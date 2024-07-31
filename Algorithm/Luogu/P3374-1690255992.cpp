#include <bits/stdc++.h>

#if !defined (ONLINE_JUDGE)
    #include "debug.hpp"
#else
    #define debug(...)
#endif

template <typename T, typename Compare = std::greater<T>>
using Heap = std::priority_queue<T, std::vector<T>, Compare>;
template <typename T>
using Stack = std::stack<T, std::vector<T>>;
template <typename T>
using Queue = std::queue<T, std::list<T>>;

using i8 = std::int8_t;
using u8 = std::uint8_t;
using i16 = std::int16_t;
using u16 = std::uint16_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
using db = double;
using ld = long double;

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

using namespace std;

// #if __cplusplus >= 202002L
// template <
//     typename Type,
//     std::regular_invocable<Type,Type> Operator = std::plus<Type>
// >
// #else
template <
    typename Type,
    typename Operator = std::plus<Type>,
    typename = std::enable_if<std::is_invocable<Operator,Type,Type>::value>::type
>
// #endif
class FenwickTree {
public:
    FenwickTree(int size, Type initValue = Type{}, Operator opt = Operator{}) 
        : bit(size + 1, initValue), opt(opt) {}

    void Assign(int size, Type value) {
        bit.Assign(size, value);
    }

    void Update(int idx, Type dx) {
        for (int i = idx + 1; i < (int)bit.size(); i += Lowbit(i)) {
            bit[i] = opt(bit[i], dx);
        }
    }

    void Fill(Type value) {
        std::fill(bit.begin(), bit.end(), value);
    }

    Type Get(int idx, Type result = {}) const {
        for (int i = idx + 1; i > 0; i -= Lowbit(i)) {
            result = opt(result, bit[i]);
        }
        return result;
    }

private:
    constexpr static int Lowbit(int x) noexcept {
        return x & -x;
    }

    std::vector<Type> bit;
    Operator opt;
};

void Main() {
    int n, q;
    cin >> n >> q;

    FenwickTree<i64> bit(n);
    for (int i = 0; i < n; i ++) {
        i64 x;
        cin >> x;
        bit.Update(i, x);
    }

    for (int _ = 1;  _ <= q; _ ++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, k;
            cin >> x >> k;
            bit.Update(x - 1, k);
        } else {
            int l, r;
            cin >> l >> r;
            l --; r --;
            cout << bit.Get(r) - bit.Get(l - 1) << '\n';
        }
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(15);

    int test = 1;
    //cin >> test;

    for (int rp = 1; test --> 0; rp ++) {
        debug(rp);
        Main();
    }
}