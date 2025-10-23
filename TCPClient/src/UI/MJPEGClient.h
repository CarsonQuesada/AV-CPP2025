// MJPEGClient.hpp
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

private:
    static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata);
    void run();

    std::string url;
    FrameProcessor& frameProcessor;
    CURL* curl;
    std::thread thread;
    std::atomic<bool> running{false};

    std::vector<unsigned char> buffer;
};
