#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const int N = 2e5 + 10;

// sval: sin sum. cval: cos sum
struct Info {
	double sval, cval;
	void init(double x) {
		sval = sin(x);
		cval = cos(x);
	}
	void update(double x) {
		auto [sin_sum, cos_sum] = *this;
		*this = {
			cos(x) * sin_sum + sin(x) * cos_sum,
			cos(x) * cos_sum - sin(x) * sin_sum
		};
	}
	friend Info operator + (const Info &a, const Info &b) {
		return Info{
			a.sval + b.sval, a.cval + b.cval
		};
	}
};

struct LazySeg {
	Info val;
	double lz;
} seg[N << 2];
double a[N];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void down(int id) {
	auto &d = seg[id].lz;
	if (d == 0) return;
	seg[id * 2].val.update(d);
	seg[id * 2 + 1].val.update(d);
	seg[id * 2].lz += d;
	seg[id * 2 + 1].lz += d;
	d = 0;
}

void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val.init(a[l]);
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void add(int l, int r, int id, int al, int ar, double d) {
	if (l == al && r == ar) {
		seg[id].val.update(d);
		seg[id].lz += d;
	} else {
		int mid = l + ((r - l) >> 1);
		down(id);
		if (ar <= mid) {
			add(l, mid, id * 2, al, ar, d);
		} else if (al > mid) {
			add(mid + 1, r, id * 2 + 1, al, ar, d);
		} else {
			add(l, mid, id * 2, al, mid, d);
			add(mid + 1, r, id * 2 + 1, mid + 1, ar, d);
		}
		rise(id);
	}
}

Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		down(id);
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
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	build(1, n, 1);

	int q;
	cin >> q;
	while (q --) {
		int opt, l, r;
		cin >> opt >> l >> r;
		if (opt == 1) {
			ld d;
			cin >> d;
			add(1, n, 1, l, r, d);
		} else {
			Info ret = query(1, n, 1, l, r);
			cout << ret.sval << '\n';
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(1);
	Solution();
}