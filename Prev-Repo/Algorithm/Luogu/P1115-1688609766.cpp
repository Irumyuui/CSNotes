#include <bits/stdc++.h>
using namespace std;

using i64 = std::int64_t;

const int N = 2e5 + 10;

struct Info {
	i64 sum, pre, suf, mx;
	Info() : sum{0}, pre{0}, suf{0}, mx{0} {}
	Info(i64 val, i64 pre, i64 suf, i64 mx) : sum{val}, pre{pre}, suf{suf}, mx{mx} {}
	void Set(auto val) {
		sum = pre = suf = mx = val;
	}
	friend Info operator + (const Info &a, const Info &b) {
		return Info {
			a.sum + b.sum,
			std::max(a.pre, a.sum + b.pre),
			std::max(a.suf + b.sum, b.suf),
			std::max({a.mx, b.mx, a.suf + b.pre})
		};
	}
};
struct Node {
	Info val;
} seg[N * 4];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void build(int l, int r, int id, const auto &a) {
	if (l + 1 == r) {
		seg[id].val.Set(a[l]);
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2, a);
		build(mid, r, id * 2 + 1, a);
		rise(id);
	}
}

Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr);
		} else if (ql >= mid) {
			return query(mid, r, id * 2 + 1, ql, qr);
		} else {
			return query(l, mid, id * 2, ql, mid) + query(mid, r, id * 2 + 1, mid, qr);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	vector<i64> a(n);
	for (auto &x : a) cin >> x;
	build(0, n, 1, a);
	cout << query(0, n, 1, 0, n).mx << '\n';
}
