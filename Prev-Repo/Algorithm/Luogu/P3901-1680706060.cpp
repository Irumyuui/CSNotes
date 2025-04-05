#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>

using namespace std;

using i64 = int64_t;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n, q;
	cin >> n >> q;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
	
	struct Query {
		int l, r, idx;
	};
	vector<Query> que(q);
	for (int t = 0; auto &[l, r, i] : que) {
		cin >> l >> r;
		i = t ++;
	}
	ranges::sort(que, [block{int(sqrt(n))}](const auto &a, const auto &b) {
		if (a.l / block != b.l / block)
			return a.l < b.l;
		if (a.l / block % 2)
			return a.r < b.r;
		return a.r > b.r;
	});

	vector<int> cnt(ranges::max(a | views::drop(1)) + 1);
	int ret = 0;
	auto Add = [&](int pos) {
		if (++ cnt[a[pos]] == 1)
			ret ++;
	};
	auto Del = [&](int pos) {
		if (cnt[a[pos]] -- == 1) 
			ret --;
	};

	vector<bool> ans(q);
	int L = 1, R = 0;
	for (const auto &[l, r, idx] : que) {
		while (L > l)
			Add(-- L);
		while (R < r)
			Add(++ R);
		while (L < l)
			Del(L ++);
		while (R > r)
			Del(R --);
		ans[idx] = (r - l + 1) == ret;
	}

	for (auto x : ans) 
		if (x) 
			cout << "Yes\n";
		else
			cout << "No\n";
}