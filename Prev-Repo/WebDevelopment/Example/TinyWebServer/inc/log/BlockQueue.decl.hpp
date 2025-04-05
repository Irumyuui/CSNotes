#pragma once

#include <condition_variable>
#include <cstddef>
#include <deque>
#include <mutex>
// #include <queue>

namespace Koro {

template <typename T>
class BlockQueue {
private:
    std::deque<T> data_queue_;
    std::size_t capacity_;
    std::mutex mutex_;
    std::condition_variable cond_consumer_;
    std::condition_variable cond_producer_;
    bool is_terminal_;

public:
    explicit BlockQueue(std::size_t capacity = 1000);
    ~BlockQueue();

    std::size_t Size(this BlockQueue &self);
    std::size_t Capacity(this BlockQueue &self);
    
    T Front(this BlockQueue &self);
    T Back(this BlockQueue &self);

    void Push(this BlockQueue &self, const T &value);
    bool TryPop(this BlockQueue &self, T &value);
    bool TryPop(this BlockQueue &self, T &value, int timeout);
    void Flush(this BlockQueue &self);
    
    void Clear(this BlockQueue &self);
    bool Empty(this BlockQueue &self);
    bool Full(this BlockQueue &self);
    void Close(this BlockQueue &self);
};

}
