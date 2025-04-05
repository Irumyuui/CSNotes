#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

void Main() {
	int n, q;
	cin >> n >> q;
	
	vector<int> col(n + 1);
	for (auto &x : col | views::drop(1)) {
		cin >> x;
	}
	
	vector<i64> cnt(ranges::max(col | views::drop(1)) + 1);
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
	vector<Query> que(q);
	for (int t = 0; auto &[l, r, id] : que) {
		cin >> l >> r;
		id = t ++;
	}
	ranges::sort(que, [block{int(sqrt(n))}](const auto &a, const auto &b) {
		if (a.l / block != b.l / block)
			return a.l < b.l;
		if (a.l / block % 2)
			return a.r < b.r;
		return a.r > b.r;
	});

	vector<pair<i64,i64>> ans(q);
	int L = 1, R = 0;
	for (auto [l, r, id] : que) {
		while (L > l)
			Add(-- L);
		while (R < r)
			Add(++ R);
		while (L < l)
			Del(L ++);
		while (R > r)
			Del(R --);
		ans[id] = {ret, i64(r - l + 1) * (r - l)};
	}

	for (auto [a, b] : ans) {
		if (a == 0 || b == 0) {
			cout << "0/1" << '\n';
		} else {
			i64 d = gcd(a, b);
			cout << a / d << '/' << b / d << '\n';
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}