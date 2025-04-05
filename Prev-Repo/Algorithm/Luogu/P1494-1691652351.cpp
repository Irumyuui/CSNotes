#include <bits/stdc++.h>
#include <execution>

using i64 = int64_t;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> col(n);
    for (int i = 0; i < n; i ++) {
        std::cin >> col[i];
        col[i] --;
    }
    
    std::vector<i64> cnt(std::ranges::max(col) + 1);
    i64 ret = 0;
	auto Add = [&](int pos) {
		if (cnt[col[pos]] >= 2)
			ret -= cnt[col[pos]] * (cnt[col[pos]] - 1);
		cnt[col[pos]] ++;
		if (cnt[col[pos]] >= 2)
			ret += cnt[col[pos]] * (cnt[col[pos]] - 1);
	};
	auto Del = [&](int pos) {
		if (cnt[col[pos]] >= 2)
			ret -= cnt[col[pos]] * (cnt[col[pos]] - 1);
		cnt[col[pos]] --;
		if (cnt[col[pos]] >= 2)
			ret += cnt[col[pos]] * (cnt[col[pos]] - 1);
	};

    struct Query {
		int l, r, id;
	};
	std::vector<Query> que(q);
	for (int t = 0; auto &[l, r, id] : que) {
		std::cin >> l >> r;
        l --; r --;
		id = t ++;
	}
	std::sort(std::execution::par_unseq, que.begin(), que.end(), [block{int(sqrt(n))}](const auto &a, const auto &b) {
		if (a.l / block != b.l / block)
			return a.l < b.l;
		if (a.l / block % 2)
			return a.r < b.r;
		return a.r > b.r;
	});

    std::vector<std::pair<i64,i64>> ans(q);
    int l = 0, r = -1;
    for (auto [ql, qr, qid] : que) {
        while (l > ql) Add(-- l);
        while (r < qr) Add(++ r);
        while (l < ql) Del(l ++);
        while (r > qr) Del(r --);
        ans[qid] = {ret, i64(r - l + 1) * (r - l)};
    }

    for (auto [a, b] : ans) {
        if (a == 0 || b == 0) {
            std::cout << "0/1" << '\n';
        } else {
            auto g = std::gcd(a, b);
            a /= g; b /= g;
            std::cout << a << '/' << b << '\n';
        }
    }
}
