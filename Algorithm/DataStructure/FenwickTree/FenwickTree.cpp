#include <vector>

template <typename T>
    requires requires(T a, T b) { a += b; }
class FenwickTree {
private:
    int n;
    std::vector<T> bit;

public:
    explicit FenwickTree(int n) : n(n), bit(n + 1) {}

    void Add(int p, int val) {
        for (int i = p; i <= n; i += (i & -i)) {
            bit[i] += val;
        }
    }

    T Sum(int p) {
        int res = 0;
        for (int i = p; i > 0; i -= (i & -i)) {
            res += bit[i];
        }
        return res;
    }
};