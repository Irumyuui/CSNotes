#include <bits/stdc++.h>

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
using f32 = float;
using f64 = double;
using f128 = long double;

#if __cplusplus >= 202002L
template <
    typename Type,
    std::regular_invocable<Type,Type> Operator = std::plus<Type>
>
#else
template <
    typename Type,
    typename Operator = std::plus<Type>,
    std::enable_if<std::is_invocable<Operator,Type,Type>::value>* = nullptr
>
#endif
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

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto &x : a) {
        std::cin >> x;
        x --;
    }

    std::vector<std::tuple<int,int,int,int,int>> query;
    query.reserve(q * 2);
    for (int i = 0; i < q; i ++) {
        int l, r, x, y;
        std::cin >> l >> r >> x >> y;
        l --; r --; x --; y --;
        query.emplace_back(l - 1, x, y, i, -1);
        query.emplace_back(r, x, y, i, 1);
    }
    
    std::ranges::sort(query);
    std::vector<int> ans(q);
    FenwickTree<int> bit(1e6 + 10);

    int tag = 0;
    for (auto [pos, l, r, qid, qd] : query) {
        while (tag < n && tag <= pos) {
            bit.Update(a[tag], 1);
            tag ++;
        }
        ans[qid] += qd * bit.Get(r, -bit.Get(l - 1));
    }
    
    for (auto x : ans) 
        std::cout << x << '\n';
}