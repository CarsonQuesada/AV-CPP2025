#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template<typename T>
class ThreadSafeQueue
{
public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(value);
        condVar.notify_one();
    }

    void push(T&& value) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::move(value));
        condVar.notify_one();
    }

    std::optional<T> tryPop() {
        std::lock_guard<std::mutex> lock(mutex);
        if (queue.empty()) return std::nullopt;
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    T waitAndPop() {
        std::unique_lock<std::mutex> lock(mutex);
        condVar.wait(lock, [this]{ return !queue.empty(); });
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mutex);
        while (!queue.empty())
            queue.pop();
    }

private:
    std::mutex mutex;
    std::queue<T> queue;
    std::condition_variable condVar;
};