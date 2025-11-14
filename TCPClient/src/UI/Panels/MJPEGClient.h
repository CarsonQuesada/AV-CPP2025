#pragma once

#include <functional>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <curl/curl.h>

#include "FrameProcessor.h"

class MJPEGClient {
public:
    MJPEGClient(const std::string& url, FrameProcessor& frameProcessor);
    ~MJPEGClient();

    void start();
    void stop();
    void setUrl(const std::string& newUrl);

private:
    static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata);
    void run();

    std::string url;
    FrameProcessor& frameProcessor;
    CURL* curl;
    std::thread thread;
    std::atomic<bool> running{false};
    std::vector<unsigned char> buffer;
    std::mutex urlMutex;

    // Helper: sleep in small increments, aborting if 'running' becomes false
    inline void sleep_with_abort(std::atomic<bool>& running, int total_ms, int step_ms = 100) {
        int waited = 0;
        while (running && waited < total_ms) {
            std::this_thread::sleep_for(std::chrono::milliseconds(step_ms));
            waited += step_ms;
        }
    }

    // (Optional) simple exponential backoff with cap and a touch of jitter
    inline int next_backoff_ms(int attempt, int base_ms = 500, int max_ms = 8000) {
        // attempt=1 -> ~500ms, 2 -> ~1000ms, 3 -> ~2000ms ... capped at max_ms (+/-10%)
        int ms = std::min(max_ms, base_ms << std::min(attempt - 1, 13)); // avoid overflow
        int jitter = ms / 10; // 10% jitter
        int delta = (rand() % (2 * jitter + 1)) - jitter; // [-jitter, +jitter]
        return std::max(100, ms + delta);
    }
};
