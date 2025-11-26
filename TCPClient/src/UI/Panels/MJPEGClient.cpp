#include "MJPEGClient.h"
#include <iostream>
#include <cstring>

MJPEGClient::MJPEGClient(const std::string& url, FrameProcessor& frameProcessor)
    : url(url), frameProcessor(frameProcessor), curl(nullptr)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

MJPEGClient::~MJPEGClient() {
    stop();
    curl_global_cleanup();
}

void MJPEGClient::start() {
    if (running.exchange(true)) return;
    buffer.clear();
    thread = std::thread(&MJPEGClient::run, this);
}

void MJPEGClient::stop() {
    if (!running.exchange(false)) return;
    if (thread.joinable()) thread.join();
    buffer.clear();
}

void MJPEGClient::setUrl(const std::string &newUrl)
{
    std::lock_guard<std::mutex> lk(urlMutex);
    url = newUrl;
}

size_t MJPEGClient::writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    size_t totalSize = size * nmemb;
    auto* client = static_cast<MJPEGClient*>(userdata);

    client->buffer.insert(client->buffer.end(), ptr, ptr + totalSize);

    while (true) {
        // Look for end of headers (\r\n\r\n)
        auto it = std::search(client->buffer.begin(), client->buffer.end(),
                              "\r\n\r\n", "\r\n\r\n" + 4);
        if (it == client->buffer.end()) {
            // Not enough data yet
            break;
        }

        // Parse headers
        std::string headers(client->buffer.begin(), it);
        size_t pos = headers.find("Content-Length:");
        if (pos == std::string::npos) {
            // If no Content-Length, discard this block and continue
            client->buffer.erase(client->buffer.begin(), it + 4);
            continue;
        }

        // Extract Content-Length value
        pos += 15; // move past "Content-Length:"
        while (pos < headers.size() && (headers[pos] == ' ' || headers[pos] == '\t'))
            pos++;
        size_t endpos = headers.find("\r\n", pos);
        //int len = std::stoi(headers.substr(pos, endpos - pos));
        size_t len = 0;
        try {
            len = static_cast<size_t>(std::stoul(headers.substr(pos, endpos - pos)));
        } catch (...) {
            // Drop this part and continue
            client->buffer.erase(client->buffer.begin(), it + 4);
            continue;
        }

        // Do we have the full frame?
        if (client->buffer.end() - (it + 4) < len) {
            // Wait for more data
            break;
        }

        // Extract JPEG frame
        auto start = it + 4;
        std::vector<unsigned char> frame(start, start + len);

        client->frameProcessor.updateFrame(frame);

        // Erase processed data (headers + frame)
        client->buffer.erase(client->buffer.begin(), start + len);
    }

    return totalSize;
}

void MJPEGClient::run() {
    const int maxRetries = 0;   // 0 => retry forever
    int attempt = 0;

    while (running && (maxRetries == 0 || attempt < maxRetries)) {
        ++attempt;

        std::string currentUrl;
        { std::lock_guard<std::mutex> lk(urlMutex); currentUrl = url; }

        // Fresh connect attempt: clear any partial MJPEG bytes
        buffer.clear();

        CURL* easy = curl_easy_init();
        if (!easy) {
            std::cerr << "[MJPEGClient] curl_easy_init() failed\n";
            frameProcessor.setStreamAvailable(false);
            break; // can't proceed without an easy handle
        }

        // ---- Configure libcurl ----
        curl_easy_setopt(easy, CURLOPT_URL, currentUrl.c_str());
        curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, &MJPEGClient::writeCallback);
        curl_easy_setopt(easy, CURLOPT_WRITEDATA, this);
        curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(easy, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(easy, CURLOPT_CONNECTTIMEOUT_MS, 3000L);

        // Progress hook so we can abort immediately when stopping
        curl_easy_setopt(easy, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(easy, CURLOPT_XFERINFOFUNCTION,
            +[](void* clientp, curl_off_t, curl_off_t, curl_off_t, curl_off_t) -> int {
                auto* self = static_cast<MJPEGClient*>(clientp);
                return self->running ? 0 : 1; // non-zero => abort transfer now
            });
        curl_easy_setopt(easy, CURLOPT_XFERINFODATA, this);

        // Optional: treat stalls as failures to trigger reconnects
        curl_easy_setopt(easy, CURLOPT_LOW_SPEED_TIME, 10L);   // seconds
        curl_easy_setopt(easy, CURLOPT_LOW_SPEED_LIMIT, 1L);   // bytes/sec

        CURLM* multi = curl_multi_init();
        curl_multi_add_handle(multi, easy);

        int still_running = 0;
        CURLMcode mc = curl_multi_perform(multi, &still_running);

        // If user stopped during connect/first perform, bail before retry logic
        if (!running) {
            curl_multi_remove_handle(multi, easy);
            curl_easy_cleanup(easy);
            curl_multi_cleanup(multi);
            break;
        }

        if (mc != CURLM_OK || still_running == 0) {
            // Initial connect failed (or ended immediately)
            int backoff = next_backoff_ms(attempt, /*base*/500, /*max*/8000);
            std::cerr << "[MJPEGClient] Connect failed (attempt " << attempt
                      << "), retrying in " << backoff << " ms...\n";

            curl_multi_remove_handle(multi, easy);
            curl_easy_cleanup(easy);
            curl_multi_cleanup(multi);
            frameProcessor.setStreamAvailable(false);

            sleep_with_abort(running, backoff);
            continue; // try again if still running
        }

        // ---- Connected: pump the stream ----
        std::cout << "[MJPEGClient] Connected and streaming...\n";
        frameProcessor.setStreamAvailable(true);

        while (running && still_running) {
            int numfds = 0;
            mc = curl_multi_wait(multi, nullptr, 0, 500, &numfds);
            if (mc != CURLM_OK) {
                std::cerr << "[MJPEGClient] curl_multi_wait() failed: "
                          << curl_multi_strerror(mc) << "\n";
                break;
            }
            curl_multi_perform(multi, &still_running);
        }

        frameProcessor.setStreamAvailable(false);

        // Cleanup the completed/failed attempt
        curl_multi_remove_handle(multi, easy);
        curl_easy_cleanup(easy);
        curl_multi_cleanup(multi);

        if (!running) break; // stop() was called — do not schedule another retry

        // If the stream ended on its own, schedule a retry with backoff
        int backoff = next_backoff_ms(attempt, /*base*/500, /*max*/8000);
        std::cerr << "[MJPEGClient] Stream ended, retrying in " << backoff << " ms...\n";
        sleep_with_abort(running, backoff);
        // loop continues if still running
    }

    std::cout << "[MJPEGClient] Thread exiting cleanly.\n";
}
