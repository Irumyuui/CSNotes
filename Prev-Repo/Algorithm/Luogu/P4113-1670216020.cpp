#include <bits/stdc++.h>
using namespace std;
using ll = std::int64_t;

#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

std::int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, c, q;
	cin >> n >> c >> q;
	vector<int> bit(n + 1);
	auto update = [&](int x, int n, int d) {
		if (x <= 0) {
			return;
		}
		for (int i = x; i <= n; i += i & -i) {
			bit[i] += d;
		}
	};
	auto query = [&](int x) {
		int ret{};
		for (int i = x; i > 0; i -= i & -i) {
			ret += bit[i];
		}
		return ret;
	};
	auto query_range = [&](int l, int r) {
		return query(r) - query(l - 1);
	};
	vector<int> col(n + 1), last1(c + 1), last2(c + 1);
	for (int i{1}; i <= n; i ++) {
		cin >> col[i];
	}
	vector<array<int,3>> que(q);
	for (int i = 0; i < q; i ++) {
		int l, r;
		cin >> l >> r;
		que[i] = {l, r, i};
	}
	sort(que.begin(), que.end(), [](const auto &a, const auto &b) {
		return a[1] != b[1] ? a[1] < b[1] : a[0] < b[0];
	});
	debug(que);
	vector<int> ans(q);
	int lst{};
	for (auto [l, r, idx] : que) {
		while (lst < r) {
			lst ++;
			int now = col[lst];
			if (last1[now] == 0) {
				last1[now] = lst;
			} else if (last2[now] == 0) {
				update(last1[now], n, 1);
				last2[now] = lst;
			} else {
				update(last1[now], n, -1);
				update(last2[now], n, 1);
				last1[now] = last2[now];
				last2[now] = lst;
			}
		}
		ans[idx] = query_range(l, r); 
	}
	for (auto a : ans) {
		cout << a << '\n';
	}
}