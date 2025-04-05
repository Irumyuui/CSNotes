#pragma once

#include <mutex>
#include <queue>

#ifndef KARUS_CHANNEL_HPP
#define KARUS_CHANNEL_HPP

namespace karus {
template <typename T> class Channel {
public:
  auto Push(const T &v) -> void;
  auto Push(T &&v) -> void;
  auto Pop() -> void;
  auto Pop(T &v) -> bool;
  auto Size() const -> std::size_t;
  auto Empty() const -> bool;
  auto Clear() -> void;

private:
  std::queue<T> q_;
  mutable std::mutex mutex_;
};
} // namespace karus

template <typename T> auto karus::Channel<T>::Push(const T &v) -> void {
  std::scoped_lock lock{this->mutex_};
  this->q_.push(v);
}

template <typename T> auto karus::Channel<T>::Push(T &&v) -> void {
  std::scoped_lock lock{this->mutex_};
  this->q_.push(std::move(v));
}

template <typename T> auto karus::Channel<T>::Pop() -> void {
  std::scoped_lock lock{this->mutex_};
  this->q_.pop();
}

template <typename T> auto karus::Channel<T>::Pop(T &v) -> bool {
  std::scoped_lock lock{this->mutex_};
  if (this->q_.empty()) {
    return false;
  }
  v = std::move(this->q_.front());
  this->q_.pop();
  return true;
}

template <typename T> auto karus::Channel<T>::Size() const -> std::size_t {
  std::scoped_lock lock{this->mutex_};
  return this->q_.size();
}

template <typename T> auto karus::Channel<T>::Empty() const -> bool {
  std::scoped_lock lock{this->mutex_};
  return this->q_.empty();
}

template <typename T> auto karus::Channel<T>::Clear() -> void {
  std::scoped_lock lock{this->mutex_};
  while (!this->q_.empty()) {
    this->q_.pop();
  }
}

#endif
