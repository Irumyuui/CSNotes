# Quick Select

主体就是 QuickSort 的改进版，只需要找到第 k 小的元素，不需要排序整个数组。

```c++
std::mt19937_64 rng(std::random_device{}());

class Solution {
   public:
    int findKth(std::span<int> a, std::size_t rk) {
        if (a.size() == 1) {
            return a.front();
        }

        int pivot = a[rng() % a.size()];
        std::size_t l = 0, i = 0, r = a.size();
        while (l < r) {
            if (a[l] < pivot) {
                std::swap(a[l ++], a[i ++]);
            } else if (a[l] > pivot) {
                std::swap(a[l], a[-- r]);
            } else {
                l ++;
            }
        }

        if (rk < i) {
            return findKth(a.first(i), rk);
        } else if (rk >= r) {
            return findKth(a.last(a.size() - r), rk - r);
        } else {
            return pivot;
        }
    }

    int findKthLargest(std::vector<int>& a, int k) {
        return findKth(a, a.size() - k);
    }
};
```
