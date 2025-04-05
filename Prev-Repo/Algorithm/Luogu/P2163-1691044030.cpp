#include <bits/stdc++.h>

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
    explicit FenwickTree(int size, Type initValue = Type{}, Operator opt = Operator{}) 
        : bit(size + 1, initValue), opt(opt) {}

    auto Assign(int size, Type value) -> void {
        assert(size >= 0);
        bit.Assign(size, value);
    }

    auto Update(int idx, Type dx) -> void {
        for (int i = idx + 1; i < (int)bit.size(); i += Lowbit(i)) {
            bit[i] = opt(bit[i], dx);
        }
    }

    auto Fill(Type value) -> void {
        std::fill(bit.begin(), bit.end(), value);
    }

    auto Get(int idx, Type result = {}) const -> Type {
        for (int i = idx + 1; i > 0; i -= Lowbit(i)) {
            result = opt(result, bit[i]);
        }
        return result;
    }

private:
    constexpr static
    auto Lowbit(int x) noexcept -> int {
        return x & -x;
    }

    std::vector<Type> bit;
    Operator opt;
};

void Main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<int,int>> point(n);
    for (auto &&[x, y] : point) {
        std::cin >> x >> y;
    }

    std::vector<std::tuple<int,int,int,int>> query;
    for (int i = 0; i < q; i ++) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        query.emplace_back(a - 1, b - 1, i, 1);
        query.emplace_back(a - 1, d, i, -1);
        query.emplace_back(c, b - 1, i, -1);
        query.emplace_back(c, d, i, 1);
    }

    std::vector<int> px(n + query.size()), py(n + query.size());
    for (int i = 0; i < n; i ++) {
        std::tie(px[i], py[i]) = point[i];
    }
    for (int i = 0; i < query.size(); i ++) {
        std::tie(px[i + n], py[i + n]) = std::tie(std::get<0>(query[i]), std::get<1>(query[i]));
    }

    std::ranges::sort(px);
    px.erase(std::ranges::unique(px).begin(), px.end());
    std::ranges::sort(py);
    py.erase(std::ranges::unique(py).begin(), py.end());

    for (auto &[x, y] : point) {
        x = std::ranges::lower_bound(px, x) - px.begin();
        y = std::ranges::lower_bound(py, y) - py.begin();
    }

    for (auto &[x, y, id, dx] : query) {
        x = std::ranges::lower_bound(px, x) - px.begin();
        y = std::ranges::lower_bound(py, y) - py.begin();
    }

    std::ranges::sort(query);
    std::ranges::sort(point);

    FenwickTree<int> bit(py.size());

    auto it = point.begin();
    std::vector<int> ans(q);
    for (auto [qx, qy, qid, qd] : query) {
        while (it != point.end() && it->first <= qx) {
            bit.Update(it->second, 1);
            ++ it;
        }
        ans[qid] += bit.Get(qy) * qd;
    }

    for (auto x : ans) std::cout << x << '\n';
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    Main();
}