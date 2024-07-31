#include <bits/stdc++.h>

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    struct Seg {
        int l, r;
    };
    std::vector<Seg> seg(n);
    for (auto &[l, r] : seg) {
        std::cin >> l >> r;
    }

    std::ranges::sort(seg, [](const auto &left, const auto &right) {
        if (left.r != right.r) {
            return left.r < right.r;
        } else {
            return left.l < right.l;
        }
    });

    std::vector<Seg> ret{seg.front()};
    ret.reserve(n);
    for (auto [l, r] : seg | std::views::drop(1)) {
        if (l >= ret.back().r) {
            ret.emplace_back(l, r);
        }
    }
    std::cout << ret.size() << '\n';
}
