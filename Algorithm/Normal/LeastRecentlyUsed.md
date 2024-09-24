# Least Recently Used

最近最少使用算法。本质思想是：维护一个窗口，满了的将使用频率低的丢掉。

```c++
class LRUCache {
private:
    int capacity_;
    std::unordered_map<int, typename std::list<std::pair<int,int>>::iterator> data_;  // 每个元素所持有的迭代器
    std::list<std::pair<int,int>> list_;  // 从 end 到 begin 表示使用频率从高到底的元素

public:
    explicit LRUCache(int capacity) : capacity_(capacity) {

    }

    int get(int key) {
        auto mp_it = data_.find(key);
        if (mp_it == data_.end()) {
            return -1;
        }

        // 取的时候需要注意一下，该元素的使用频率刷新了。
        auto value = mp_it->second->second;
        list_.erase(mp_it->second);
        list_.emplace_back(key, value);
        mp_it->second = std::prev(list_.end());

        return value;
    }

    void put(int key, int value) {
        // 是不是之前有用过，有就提取作为高优先级
        if (auto it = data_.find(key); it != data_.end()) {
            list_.erase(it->second);
            list_.emplace_back(key, value);
            it->second = std::prev(list_.end());
            return;
        }

        // 如果满了，那么就删除掉一个，再放进去
        if (data_.size() == capacity_) {
            data_.erase(list_.front().first);
            list_.erase(list_.begin());
        }

        list_.emplace_back(key, value);
        data_[key] = std::prev(list_.end());
        return;
    }
};
```
