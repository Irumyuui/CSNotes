#pragma once

#include "BlockQueue.decl.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <mutex>

namespace Koro {

template <typename T>
BlockQueue<T>::BlockQueue(std::size_t capacity) : capacity_(capacity), is_terminal_(false) {
    assert(capacity > 0);
}

template <typename T>
BlockQueue<T>::~BlockQueue() {
    Close();
}


template <typename T>
std::size_t BlockQueue<T>::Size(this BlockQueue &self) {
    std::scoped_lock lock{self.data_queue_};
    return self.data_queue_.size();
}

template <typename T>
std::size_t BlockQueue<T>::Capacity(this BlockQueue &self) {
    std::scoped_lock lock{self.data_queue_};
    return self.capacity_;
}

template <typename T>
T BlockQueue<T>::Front(this BlockQueue &self) {
    std::scoped_lock lock{self.data_queue_};
    return self.data_queue_.front();
}

template <typename T>
T BlockQueue<T>::Back(this BlockQueue &self) {
    std::scoped_lock lock{self.data_queue_};
    return self.data_queue_.back();
}

template <typename T>
void BlockQueue<T>::Push(this BlockQueue &self, const T &value) {
    std::unique_lock lock{self.mutex_};
    while (self.data_queue_.size() >= self.capacity_) {
        self.cond_producer_.wait(lock);
    }
    self.data_queue_.push_back(value);
    self.cond_consumer_.notify_one();
}

template <typename T>
bool BlockQueue<T>::TryPop(this BlockQueue &self, T &result) {
    std::unique_lock lock{self.data_queue_};
    while (self.data_queue_.empty()) {
        self.cond_consumer_.wait(lock);
        if (self.is_terminal_) {
            return false;
        }
    }
    result = std::move(self.data_queue_.front());
    self.data_queue_.pop_front();
    self.cond_producer_.notify_one();
    return true;
}

template <typename T>
bool BlockQueue<T>::TryPop(this BlockQueue &self, T &result, int timeout) {
    std::unique_lock lock{self.mutex_};
    while (self.data_queue_.empty()) {
        if (self.cond_consumer_.wait_for(lock, std::chrono::seconds(timeout)) == std::cv_status::timeout || self.is_terminal_) {
            return false;
        }
    }
    result = std::move(self.data_queue_.front());
    self.data_queue_.pop_front();
    self.cond_producer_.notify_one();
    return true;
}

template <typename T>
void BlockQueue<T>::Flush(this BlockQueue &self) {
    self.cond_consumer_.notify_one();
}

template <typename T>
void BlockQueue<T>::Clear(this BlockQueue &self) {
    std::scoped_lock lock{self.data_queue_};
    self.data_queue_.clear();
}

template <typename T>
bool BlockQueue<T>::Empty(this BlockQueue &self) {
    std::scoped_lock lock{self.data_queue_};
    return self.data_queue_.empty();
}

template <typename T>
bool BlockQueue<T>::Full(this BlockQueue &self) {
    std::scoped_lock lock{self.data_queue_};
    return self.data_queue_.size() >= self.capacity_;
}

template <typename T>
void BlockQueue<T>::Close(this BlockQueue &self) {
    {
        std::scoped_lock lock{self.mutex_};
        self.data_queue_.clear();
        self.is_terminal_ = true;
    }
    self.cond_consumer_.notify_all();
    self.cond_producer_.notify_all();
}

}
