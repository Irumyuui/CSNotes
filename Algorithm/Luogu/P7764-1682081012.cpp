#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n, q;
	cin >> n >> q;

	vector<int> a(n + 1);
	for (auto &&x : a | views::drop(1)) {
		cin >> x;
	}

	vector<array<int,3>> que(q);
	for (int i = 0; auto &[l, r, id] : que) {
		cin >> l >> r;
		id = i ++;
	}
	ranges::sort(que, [bk=int(sqrt(n))](const auto &a, const auto &b) -> bool {
		if (a[0] / bk != b[0] / bk) 
			return a[0] < b[0];
		if (a[0] / bk % 2)
			return a[1] < b[1];
		return a[1] > b[1];
	});

	vector<int> cnt(ranges::max(a | views::drop(1)) + 1);
	int ret = 0;
	auto Add = [&](int pos) -> void {
		cnt[a[pos]] ++;
		if (cnt[a[pos]] == 2) {
			ret ++;
		} else if (cnt[a[pos]] == 3) {
			ret --;
		}
	};
	auto Del = [&](int pos) -> void {
		cnt[a[pos]] --;
		if (cnt[a[pos]] == 2) {
			ret ++;
		} else if (cnt[a[pos]] == 1) {
			ret --;
		}
	};
	vector<int> ans(q);
	int l = 1, r = 0;
	for (auto [ql, qr, id] : que) {
		while (l > ql)
			Add(-- l);
		while (r < qr)
			Add(++ r);
		while (l < ql)
			Del(l ++);
		while (r > qr)
			Del(r --);
		ans[id] = ret;
	}

	for (auto x : ans) {
		cout << x << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}