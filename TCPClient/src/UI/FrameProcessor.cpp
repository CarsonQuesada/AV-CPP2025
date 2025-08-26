#include "FrameProcessor.h"

#include <cstring>
#include <iostream>

FrameProcessor::FrameProcessor() 
{
}

FrameProcessor::~FrameProcessor() 
{
    stop();
}

void FrameProcessor::start() {
    running = true;
    worker = std::thread(&FrameProcessor::workerThread, this);
}

void FrameProcessor::stop() {
    running = false;
    frameReady.notify_all();
    if (worker.joinable())
        worker.join();
}

void FrameProcessor::updateFrame(const std::vector<unsigned char>& newFrame) {
    {
        std::lock_guard<std::mutex> lock(jpegMutex);
        jpegFrame = newFrame;
    }
    frameReady.notify_one();
}

Frame FrameProcessor::getFrame() {
    std::lock_guard<std::mutex> lock(frameMut);
    std::cout << "Made it 5" << std::endl;
    return frame;
}

void FrameProcessor::workerThread() {
    while (running) {
        std::unique_lock<std::mutex> lock(jpegMutex);
        frameReady.wait(lock, [&]() { return !jpegFrame.empty() || !running; });
        std::cout << "Frame Ready" << std::endl;

        if (!running) break;

        std::vector<unsigned char> localCopy = jpegFrame;
        jpegFrame.clear();
        lock.unlock();

        std::cout << "Made it 3" << std::endl;
        int width, height, channels;
        unsigned char* imageData = stbi_load_from_memory(localCopy.data(), static_cast<int>(localCopy.size()), &width, &height, &channels, 3);
        std::cout << "Made it 4" << std::endl;
        if (!imageData || width <= 0 || height <= 0 || channels != 3) {
            std::cerr << "Failed to decode JPEG. width=" << width << ", height=" << height << ", channels=" << channels << std::endl;
            const char* error = stbi_failure_reason();
            std::cerr << "ERROR: " << (error ? error : "unknown") << std::endl;
            {
                std::lock_guard<std::mutex> lock(frameMut);
                frame.ready = false;
                frame.pixels.clear();  // Clear just in case
                frame.width = frame.height = 0;
            }
            continue;
        }

        size_t pixelCount = static_cast<size_t>(width) * height * 3;
        if (pixelCount > 100000000) { // Arbitrary sanity cap
            std::cerr << "Abnormal pixel count! Aborting.\n";
            stbi_image_free(imageData);
            continue;
        }

        std::lock_guard<std::mutex> frameLock(frameMut);
        frame.pixels.assign(imageData, imageData + (size_t(width) * height * 3));
        frame.width = width;
        frame.height = height;
        frame.ready = true;
        std::cout << "set frame ready to true" << std::endl;

        stbi_image_free(imageData);
    }
}
