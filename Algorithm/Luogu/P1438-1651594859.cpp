#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e6+ 10;

int n, m;
ll a[N];
struct node {
	ll val, ad;
} seg[N * 4];

void update(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}
void down(int l, int r, int id) {
	if (seg[id].ad) {
		auto &ad = seg[id].ad;
		int mid = l + r >> 1;
		seg[id * 2].val += ad * (mid - l + 1);
		seg[id * 2].ad += ad;
		seg[id * 2 + 1].val += ad * (r - mid);
		seg[id * 2 + 1].ad += ad;
		ad = 0;
	}
}
void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val = a[l];
	} else {
		int mid = l + r >> 1;
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		update(id);
	}
}
void modify(int l, int r, int id, int pos, ll val) {
	if (l == r) {
		seg[id].val += val;
		seg[id].ad += val;
	} else {
		down(l, r, id);
		int mid = l + r >> 1;
		if (pos <= mid) {
			modify(l, mid, id * 2, pos, val);
		} else {
			modify(mid + 1, r, id * 2 + 1, pos, val);
		}
		update(id);
	}
}
void modify(int l, int r, int id, int sl, int sr, ll val) {
	if (sl == l && r == sr) {
		seg[id].val += (r - l + 1) * val;
		seg[id].ad += val;
	} else {
		down(l, r, id);
		int mid = l + r >> 1;
		if (sr <= mid) {
			modify(l, mid, id * 2, sl, sr, val);
		} else if (sl > mid) {
			modify(mid + 1, r, id * 2 + 1, sl, sr, val);
		} else {
			modify(l, mid, id * 2, sl, mid, val);
			modify(mid + 1, r, id * 2 + 1, mid + 1, sr, val);
		}
		update(id);
	}
}
ll query(int l, int r, int id, int ql, int qr) {
	if (ql == l && qr == r) {
		return seg[id].val;
	} else {
		down(l, r, id);
		int mid = l + r >> 1;
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			return query(l, mid, id * 2, ql, mid) 
			+ query(mid + 1, r, id * 2 + 1, mid + 1, qr);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	for (int i = n; i > 1; -- i) {
		a[i] -= a[i - 1];
	}

	build(1, n, 1);
	for (int opt; m --; ) {
		cin >> opt;
		if (opt == 1) {
			int l, r;
			ll k, d;
			cin >> l >> r >> k >> d;

			if (l <= n) modify(1, n, 1, l, k);
			if (l + 1 <= r && l + 1 <= n) modify(1, n, 1, l + 1, r, d);
			if (r + 1 <= n) modify(1, n, 1, r + 1, -((r - l) * d + k));

		} else {
			int p;
			cin >> p;
			auto ans = query(1, n, 1, 1, p);
			cout << ans << '\n';
		}
	}
}