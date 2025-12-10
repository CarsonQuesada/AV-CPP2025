#pragma once
#include <string>
#include <atomic>
#include <thread>
#include <mutex>

#include "FrameProcessor.h"

struct AVFormatContext;
struct AVCodecContext;
struct SwsContext;
struct AVFrame;
struct AVPacket;

class FfmpegRtspClient {
public:
    FfmpegRtspClient(const std::string& url, FrameProcessor& sink);
    ~FfmpegRtspClient();

    void start();
    void stop();
    void setUrl(const std::string& u);

private:
    void run();

    std::string url_;
    std::mutex urlMtx_;
    FrameProcessor& out_;

    std::atomic<bool> running_{false};
    std::thread th_;
};
