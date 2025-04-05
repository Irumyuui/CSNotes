#pragma once

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <functional>
#include <limits>
#include <optional>
#include <set>
#include <unordered_map>
#include <utility>

namespace Koro {
  class TimeScheduler {
  private:
    struct TaskInfo {
      std::size_t task_id_;                                             // Task's id.
      std::chrono::high_resolution_clock::time_point time_point_;       // Task time point.
      std::function<void()> fn_;                                        // The task.

      constexpr auto operator <=> (this const TaskInfo &self, const TaskInfo &other) noexcept {
        return self.time_point_ <=> other.time_point_; 
      }
    };

  public:
    void Push(std::size_t task_id, std::chrono::milliseconds delay, std::function<void()> fn) {
      auto time_point = std::chrono::high_resolution_clock::now() + delay;
      if (auto it = id_to_iter_.find(task_id); it != id_to_iter_.end()) {
        auto fn = std::move(it->second->fn_);
        tasks_.erase(it->second);
        it->second = tasks_.emplace(task_id, time_point, std::move(fn));
      } else {
        auto new_it = tasks_.emplace(task_id, time_point, std::move(fn));
        id_to_iter_[task_id] = new_it;
      }
    }

    // If get this task, then it will be erased.
    std::optional<std::function<void()>> GetTask(std::size_t task_id) {
      if (auto it = id_to_iter_.find(task_id); it != id_to_iter_.end()) [[likely]] {
        auto fn = std::move(it->second->fn_);
        tasks_.erase(it->second);
        id_to_iter_.erase(it);
        return fn;
      } else {
        return std::nullopt;
      }
    }

    std::optional<std::function<void()>> PopTop() {
      if (tasks_.empty()) {
        return std::nullopt;
      }
      auto fn = std::move(tasks_.begin()->fn_);
      id_to_iter_.erase(tasks_.begin()->task_id_);
      tasks_.erase(tasks_.begin());
      return fn;
    }

    void Clear() {
      tasks_.clear();
      id_to_iter_.clear();
    }

    std::size_t Size() const noexcept {
      return tasks_.size();
    }

    void AdjustDelay(std::size_t task_id, std::chrono::milliseconds delay) {
      if (auto it = id_to_iter_.find(task_id); it != id_to_iter_.end()) [[likely]] {
        auto time_point = std::chrono::high_resolution_clock::now() + delay;
        auto fn = std::move(it->second->fn_);
        tasks_.erase(it->second);
        it->second = tasks_.emplace(task_id, time_point, std::move(fn));        
      }
    }

    void Tick() {
      while (!tasks_.empty()) {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(tasks_.begin()->time_point_ - std::chrono::high_resolution_clock::now()).count() > 0) {
          break;
        }
        auto fn = PopTop();
        assert(fn.has_value());
        (*fn)();
      }
    }

    bool Empty() const noexcept {
      return tasks_.empty();
    }

    auto GetNextTick() {
      Tick();
      std::size_t res = std::numeric_limits<std::size_t>::max();

      if (!Empty()) {
        // if (auto tick = std::chrono::duration<std::chrono::milliseconds>(tasks_.begin()->time_point_ - std::chrono::high_resolution_clock::now()).count(); tick > 0)
        auto tick = std::chrono::duration_cast<std::chrono::milliseconds>(tasks_.begin()->time_point_ - std::chrono::high_resolution_clock::now()).count();
        res = static_cast<std::size_t>(std::max(tick, static_cast<decltype(tick)>(0)));
      }

      return res;
    }

  private:
    std::multiset<TaskInfo> tasks_;
    std::unordered_map<std::size_t, typename std::multiset<TaskInfo>::iterator> id_to_iter_;
  };

  // class TimeScheduler {
  // private:

  //   struct NodeInfo {
  //     std::size_t task_id_;                                             // Task's id.
  //     std::chrono::high_resolution_clock::time_point time_point_;       // Task time point.
  //     std::function<void()> fn_;                                        // The task.

  //     // explicit NodeInfo(std::size_t task_id, std::chrono::high_resolution_clock::time_point time_point, std::function<void()> fn)
  //     //   : task_id_(task_id), time_point_(time_point), fn_(std::move(fn)) {

  //     // }

  //     constexpr auto operator <=> (this const NodeInfo &self, const NodeInfo &other) noexcept {
  //       return self.time_point_ <=> other.time_point_; 
  //     }
  //   };
    
  // public:
  //   void push(this TimeScheduler &self, std::size_t task_id, std::size_t time_out, std::function<void()> fn) {
  //     auto time_point = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds{time_out};
  //     if (auto it = self.id_to_index_.find(task_id); it != self.id_to_index_.end()) {
  //       auto index = self.heap_.size();
  //       self.heap_.emplace_back(task_id, time_point, std::move(fn));
  //       self.id_to_index_[task_id] = index;
  //       self.up(index);
  //     } else {
  //       auto index = it->second;
  //       self.heap_[index].time_point_ = time_point;
  //       self.heap_[index].fn_ = std::move(fn);
  //       if (!self.try_down(index)) {
  //         self.try_up(index);
  //       }
  //     }
  //   }

  //   void adjust_time_out(std::size_t task_id, std::size_t time_out) {
  //     if (!id_to_index_.contains(task_id)) {
  //       return;
  //     }
  //     auto time_point = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds{time_out};
  //     auto index = id_to_index_[task_id];
  //     heap_[index].time_point_ = time_point;
  //     if (!try_down(index)) {
  //       try_up(index);
  //     }
  //   }

  //   void tick() {
  //     while (!heap_.empty()) {
  //       if (std::chrono::duration_cast<std::chrono::milliseconds>(heap_[0].time_point_ - std::chrono::high_resolution_clock::now()).count() > 0) {
  //         break;
  //       }

  //     }
  //   }

  //   void achieve_task(this TimeScheduler &self, std::size_t task_id) {
  //     if (self.empty() || !self.id_to_index_.contains(task_id)) {
  //       return;
  //     }

  //     auto index = self.id_to_index_[task_id];
  //     auto task_fn = std::move(self.heap_[index].fn_);
  //     self.delete_by_index(index);

  //     task_fn();
  //   }

  //   std::optional<std::function<void()>> pop_task(this TimeScheduler &self, std::size_t task_id) {
  //     if (self.empty() || !self.id_to_index_.contains(task_id)) {
  //       return std::nullopt;
  //     }

  //     auto index = self.id_to_index_[task_id];
  //     auto task_fn = std::move(self.heap_[index].fn_);
  //     self.delete_by_index(index);

  //     return task_fn;
  //   }

  //   bool empty(this const TimeScheduler &self) noexcept {
  //     return self.heap_.empty();
  //   }

  //   void clear(this TimeScheduler &self) {
  //     self.heap_.clear();
  //     self.id_to_index_.clear();
  //   }

  //   void delete_by_task_id(std::size_t task_id) {
  //     if (auto it = id_to_index_.find(task_id); it != id_to_index_.end()) {
  //       auto index = it->second;
  //       delete_by_index(index);
  //     }
  //   }

  // private:
  //   void delete_by_index(std::size_t idx) {
  //     heap_[idx].time_point_ = std::numeric_limits<std::chrono::high_resolution_clock::time_point>::max();
  //     down(idx);
  //     auto id = heap_.back().task_id_;
  //     id_to_index_.erase(id);
  //     heap_.pop_back();
  //   }

  //   void swap_node(std::size_t a, std::size_t b) {
  //     std::swap(heap_[a], heap_[b]);
  //     id_to_index_[heap_[a].task_id_] = a;
  //     id_to_index_[heap_[b].task_id_] = b;
  //   }

  //   void up(std::size_t idx) {
  //     while (idx > 0 && heap_[idx] < heap_[(idx - 1) / 2]) {
  //       // std::swap(heap_[(idx - 1) / 2], heap_[idx]);
  //       swap_node((idx - 1) / 2, idx);
  //       idx = (idx - 1) / 2;
  //     }
  //   }

  //   bool try_up(std::size_t idx) {
  //     auto id = heap_[idx].task_id_;
  //     up(idx);
  //     return id_to_index_[id] != idx;
  //   }

  //   void down(std::size_t idx) {
  //     while (idx * 2 + 1 < heap_.size()) {
  //       auto ch = idx * 2 + 1;
  //       if (ch + 1 < heap_.size() && heap_[ch + 1] < heap_[ch]) {
  //         ch += 1;
  //       }
  //       if (heap_[idx] < heap_[ch]) {
  //         break;
  //       }
  //       // std::swap(heap_[idx], heap_[ch]);
  //       swap_node(idx, ch);
  //       idx = ch;
  //     }
  //   }

  //   bool try_down(std::size_t idx) {
  //     auto id = heap_[idx].task_id_;
  //     down(idx);
  //     return id_to_index_[id] != idx;
  //   }
    
  // private:
  //   std::vector<NodeInfo> heap_;
  //   std::unordered_map<std::size_t, std::size_t> id_to_index_;
  // };
}
