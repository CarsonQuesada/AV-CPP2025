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

    // Look for JPEG frame boundaries: 0xFFD8 (start) and 0xFFD9 (end)
    while (true) {
        auto startIt = std::search(client->buffer.begin(), client->buffer.end(),
                                   std::begin("\xFF\xD8"), std::end("\xFF\xD8") - 1);
        auto endIt = std::search(client->buffer.begin(), client->buffer.end(),
                                 std::begin("\xFF\xD9"), std::end("\xFF\xD9") - 1);
        if (startIt != client->buffer.end() && endIt != client->buffer.end() && endIt > startIt) {
            endIt += 2; // Include the end marker
            std::vector<unsigned char> frame(startIt, endIt);
            client->frameProcessor.updateFrame(frame);
            client->buffer.erase(client->buffer.begin(), endIt);
        } else {
            break;
        }
    }

    return totalSize;
}

void MJPEGClient::run() {
    while (running) {
        CURL* curl = curl_easy_init();
        if (!curl) {
            std::cerr << "Failed to initialize curl" << std::endl;
            frameProcessor.setStreamAvailable(false);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &MJPEGClient::writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L); // Retry every 5s
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3L); // Connection max 3s

        std::cout << "[MJPEGClient] Connected and streaming..." << std::endl;
        frameProcessor.setStreamAvailable(true);
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "[MJPEGClient] curl_easy_perform() failed: "
                    << curl_easy_strerror(res) << std::endl;
            frameProcessor.setStreamAvailable(false);
        }

        std::cout << "[MJPEGClient] cleaning up " << std::endl;
        curl_easy_cleanup(curl);

        // Delay before retrying (to avoid busy loop)
        if (running) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}
