#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 10;
struct que {
	int l, r, id;
} q[N];
struct info {
	int val, id;
} a[N];
struct date {
	int l, r;
} p[N];
struct node {
	ll cnt;
} seg[N << 2];
inline void rise(int id) {
	seg[id].cnt = seg[id * 2].cnt + seg[id * 2 + 1].cnt;
}
void add(int l, int r, int id, int pos, int d = 1) {
	if (l == r) {
		seg[id].cnt += d;
	} else {
		int mid = l + ((r - l) >> 1);
		if (pos <= mid) {
			add(l, mid, id * 2, pos, d);
		} else {
			add(mid + 1, r ,id * 2 + 1, pos, d);
		}
		rise(id);
	}
}
ll ask(int l, int r, int id, int sl, int sr) {
	if (l == sl && r == sr) {
		return seg[id].cnt;
	} else {
		int mid = l + ((r - l) >> 1);
		if (sr <= mid) {
			return ask(l, mid, id * 2, sl, sr);
		} else if (sl > mid) {
			return ask(mid + 1, r, id * 2 + 1, sl, sr);
		} else {
			return ask(l, mid, id * 2, sl, mid) + ask(mid + 1, r, id * 2 + 1, mid + 1, sr);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
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
		return a.r != b.r ? a.r < b.r : a.l < b.l;
	});
	vector<date> p;
	auto work = [&](int l, int r) -> void {
		if (l > r) swap(l, r);
		p.push_back({l, r});
	};
	for (int i = 1; i <= n; ++ i) {
		if (i == 1) {
			work(a[i].id, a[i + 1].id);
		} else if (i == n) {
			work(a[i].id, a[i - 1].id);
		} else {
			int d1 = abs(a[i].val - a[i - 1].val), d2 = abs(a[i].val - a[i + 1].val);
			if (d1 == d2) {
				work(a[i].id, a[i - 1].id);
				work(a[i].id, a[i + 1].id);
			} else if (d1 < d2) {
				work(a[i].id, a[i - 1].id);
			} else {
				work(a[i].id, a[i + 1].id);
			}
		}
	}
	sort(begin(p), end(p), [](const auto &a, const auto &b) {
		return a.r != b.r ? a.r < b.r : a.l < b.l;
	});
	ll ans = 0;
	int pos = 0;
	for (int i = 1; i <= m; ++ i) {

		while (pos < int(p.size()) && p[pos].r <= q[i].r) {
			add(1, n, 1, p[pos].l, 1);
			pos ++;
		}
		ans += q[i].id * ask(1, n, 1, q[i].l, q[i].r);
	}
	cout << ans;
}