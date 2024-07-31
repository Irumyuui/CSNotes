#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 10;
struct info {
	int val, id;
} a[N];
struct que {
	int l, r, id;
} q[N];
inline int lowbit(int x) {
	return x & -x;
}
int n, m;
ll bit[N];
void add(int x, int d) {
	for (; x <= n; x += lowbit(x)) {
		bit[x] += d;
	}
}
ll ask(int x) {
	ll ret = 0;
	for (; x > 0; x -= lowbit(x)) {
		ret += bit[x];	
	}
	return ret;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;

	if (n == 1) {
		cout << 0;
		return 0;
	}
	
	for (int i = 1; i <= n; ++ i) {
		int x;
		cin >> x;
		a[i] = {x, i};
	}
	for (int i = 1; i <= m; ++ i) {
		int l, r;
		cin >> l >> r;
		q[i] = {l, r, i};
	}

	sort(a + 1, a + 1 + n, [](const auto &a, const auto &b) {
		return a.val < b.val;
	});
	sort(q + 1, q + 1 + m, [](const auto &a, const auto &b) {
		// return a.l != b.l ? a.l < b.l : a.r < b.r;
		return a.r != b.r ? a.r < b.r : a.l < b.l;
	});
	vector<pair<int,int>> p;
	function<void(int,int)> addp = [&p](int l, int r) -> void {
		p.push_back({
			min(l, r),
			max(l, r)
		});
	};

	for (int i = 1; i <= n; ++ i) {
		if (i == 1) {
			addp(a[i].id, a[i + 1].id);
		} else if (i == n) {
			addp(a[i].id, a[i - 1].id);
		} else {
			int d1 = abs(a[i].val - a[i - 1].val), d2 =  abs(a[i].val - a[i + 1].val);
			if (d1 == d2) {
				addp(a[i].id, a[i + 1].id);
				addp(a[i].id, a[i - 1].id);
			} else if (d1 < d2) {
				addp(a[i].id, a[i - 1].id);
			} else {
				addp(a[i].id, a[i + 1].id);
			}
		}
	}
	sort(begin(p), end(p), [](const auto &a, const auto &b) {
		return a.second != b.second ? a.second < b.second : a.first < b.first;
	});

	ll ans = 0;
	int pos = 0;
	for (int i = 1; i <= m; ++ i) {
		auto [ql, qr, id] = q[i];
		while (pos < int(p.size()) && p[pos].second <= qr) {
			add(p[pos].first, 1);
			pos ++;
		}
		ll ret = pos - ask(ql - 1);
		ans += ret * id;
	}
	cout << ans << '\n';
}