#pragma once
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <stb_image.h>

struct Frame {
    std::vector<unsigned char> pixels; // RGB format
    int width = 0;
    int height = 0;
    bool ready = false;
};

class FrameProcessor {
public:
    FrameProcessor();
    ~FrameProcessor();

    void start();
    void stop();

    // Called from network thread to push JPEG bytes
    void updateFrame(const std::vector<unsigned char>& newFrame);

    // Called from UI thread to get current OpenGL texture
    Frame getFrame();

    inline void setStreamAvailable(bool available) {
        streamAvailable.store(available);
    }
    inline bool isStreamAvailable() const {
        return streamAvailable.load();
    }
private:
    void workerThread();

    std::vector<unsigned char> jpegFrame;
    mutable std::mutex jpegMutex;
    std::condition_variable frameReady;
    std::atomic<bool> running{false};
    std::atomic<bool> streamAvailable{false};

    std::mutex frameMut;
    Frame frame;

    std::thread worker;
};
