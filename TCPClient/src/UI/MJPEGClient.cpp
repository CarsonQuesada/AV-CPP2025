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
    if (running) return;
    running = true;
    thread = std::thread(&MJPEGClient::run, this);
}

void MJPEGClient::stop() {
    if (!running) return;
    running = false;
    if (thread.joinable())
        thread.join();
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
        int len = std::stoi(headers.substr(pos, endpos - pos));

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
    CURL* easy = curl_easy_init();
    if (!easy) {
        std::cerr << "[MJPEGClient] Failed to initialize curl" << std::endl;
        frameProcessor.setStreamAvailable(false);
        return;
    }

    curl_easy_setopt(easy, CURLOPT_URL, url.c_str());
    curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, &MJPEGClient::writeCallback);
    curl_easy_setopt(easy, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(easy, CURLOPT_TCP_KEEPALIVE, 1L);
    curl_easy_setopt(easy, CURLOPT_CONNECTTIMEOUT_MS, 3000L); // max time to connect

    CURLM* multi = curl_multi_init();
    curl_multi_add_handle(multi, easy);

    int still_running = 0;
    curl_multi_perform(multi, &still_running);

    std::cout << "[MJPEGClient] Connected and streaming (multi interface)..." << std::endl;
    frameProcessor.setStreamAvailable(true);

    while (running && still_running) {
        int numfds = 0;
        CURLMcode mc = curl_multi_wait(multi, nullptr, 0, 500, &numfds);
        if (mc != CURLM_OK) {
            std::cerr << "[MJPEGClient] curl_multi_wait() failed: " << curl_multi_strerror(mc) << std::endl;
            break;
        }

        curl_multi_perform(multi, &still_running);
    }

    curl_multi_remove_handle(multi, easy);
    curl_easy_cleanup(easy);
    curl_multi_cleanup(multi);

    std::cout << "[MJPEGClient] Thread exiting cleanly." << std::endl;
    frameProcessor.setStreamAvailable(false);
}
