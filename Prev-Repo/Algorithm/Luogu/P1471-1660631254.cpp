/* P1471 方差 */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

const int N = 1e5 + 10;
double a[N];

struct Info {
	double val, pval;
	friend Info operator + (const Info &a, const Info &b) {
		return Info{a.val + b.val, a.pval + b.pval};
	}
};
struct LzSeg {
	Info val;
	double lz;
} seg[N << 2];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void down(int l, int r, int id) {
	auto &d = seg[id].lz;
	if (d == 0) return;
	int mid = l + ((r - l) >> 1);

	seg[id * 2].val.pval += 2 * d * seg[id * 2].val.val + (mid - l + 1) * d * d;
	seg[id * 2 + 1].val.pval += 2 * d * seg[id * 2 + 1].val.val + (r - mid) * d * d;

	seg[id * 2].val.val += (mid - l + 1) * d;
	seg[id * 2 + 1].val.val += (r - mid) * d;

	seg[id * 2].lz += d;
	seg[id * 2 + 1].lz += d;

	d = 0;
}

void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val.val = a[l];
		seg[id].val.pval = a[l] * a[l];
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void add(int l, int r, int id, int al, int ar, double d) {
	if (l == al && r == ar) {
		seg[id].val.pval += 2 * d * seg[id].val.val + (r - l + 1) * d * d;
		seg[id].val.val += (r - l + 1) * d;
		seg[id].lz += d;
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (ar <= mid) {
			add(l, mid, id * 2, al, ar, d);
		} else if (al > mid) {
			add(mid + 1, r, id * 2 + 1, al, ar, d);
		} else {
			add(l, mid, id * 2, al, mid, d); add(mid + 1, r, id * 2 + 1, mid + 1, ar, d);
		}
		rise(id);
	}
}

Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
		}
	}
}

void Solution() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	build(1, n, 1);

	cout << fixed << setprecision(4);

	while (m --) {
		int opt, l, r;
		cin >> opt >> l >> r;
		if (opt == 1) {
			double k;
			cin >> k;
			add(1, n, 1, l, r, k);
		} else if (opt == 2) {
			auto [sum, psum] = query(1, n, 1, l, r);
			double ave = sum / (r - l + 1);
			cout << ave << '\n';
		} else {
			auto [sum, psum] = query(1, n, 1, l, r);
			double ave = sum / (r - l + 1);
			double ans = psum / (r - l + 1) - ave * ave;
			cout << ans << '\n';
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}