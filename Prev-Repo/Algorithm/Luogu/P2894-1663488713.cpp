#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

struct Info {
	int pre_val, suf_val, max_val;
	int l, r;
	friend Info operator + (const Info &a, const Info &b) {
		return Info {
			a.pre_val + (a.pre_val == a.r - a.l + 1 ? b.pre_val : 0),
			b.suf_val + (b.suf_val == b.r - b.l + 1 ? a.suf_val : 0),
			max({a.max_val, b.max_val, a.suf_val + b.pre_val}),
			a.l, b.r			
		};
	}
};
struct Node {
	Info val;
	int lz_c;
	bool mk_c;
} seg[N << 2];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}
void update(int l, int r, int id, int c) {
	seg[id].val.max_val = seg[id].val.pre_val = seg[id].val.suf_val = (r - l + 1) * c;
	seg[id].lz_c = c;
	seg[id].mk_c = true;
}
void down(int l, int r, int id) {
	if (seg[id].mk_c) {
		int mid = l + ((r - l) >> 1);
		update(l, mid, id * 2, seg[id].lz_c);
		update(mid + 1, r, id * 2 + 1, seg[id].lz_c);
		seg[id].mk_c = false;
	}
}

void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val.l = seg[id].val.r = l;
		seg[id].val.max_val = seg[id].val.pre_val = seg[id].val.suf_val = 1;
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void modify(int l, int r, int id, int ml, int mr, int c) {
	if (l == ml && r == mr) {
		update(l, r, id, c);
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (mr <= mid) {
			modify(l, mid, id * 2, ml, mr, c);
		} else if (ml > mid) {
			modify(mid + 1, r, id * 2 + 1, ml, mr, c);
		} else {
			modify(l, mid, id * 2, ml, mid, c);
			modify(mid + 1, r, id * 2 + 1, mid + 1, mr, c);
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

int query(int l, int r, int id, int ql, int qr, int len) {
	if (seg[id].val.max_val < len) {
		return -1;
	}
	if (l == ql && r == qr) {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (seg[id * 2].val.max_val >= len) {
			return query(l, mid, id * 2, ql, mid, len);
		} else if (seg[id * 2].val.suf_val + seg[id * 2 + 1].val.pre_val >= len) {
			return seg[id * 2].val.r - seg[id * 2].val.suf_val + 1;
		} else {
			return query(mid + 1, r, id * 2 + 1, mid + 1, qr, len);
		}
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr, len);
		} else if (ql > mid) {
			return query(mid + 1, r, id * 2 + 1, ql, qr, len);
		} else {
			if (seg[id * 2].val.max_val >= len) {
				return query(l, mid, id * 2, ql, mid, len);
			} else if (seg[id * 2].val.suf_val + seg[id * 2 + 1].val.pre_val >= len && seg[id * 2].val.r - seg[id * 2].val.suf_val + 1 >= ql) {
				return seg[id * 2].val.r - seg[id * 2].val.suf_val + 1;
			} else {
				return query(mid + 1, r, id * 2 + 1, mid + 1, qr, len);
			}
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	build(1, n, 1);
	while (m --> 0) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int len;
			cin >> len;
			int ret = query(1, n, 1, 1, n, len);
			if (ret == -1) {
				cout << 0 << '\n';
			} else {
				cout << ret << '\n';
				modify(1, n, 1, ret, ret + len - 1, 0);
			}
		} else {
			int l, r;
			cin >> l >> r;
			modify(1, n, 1, l, r + l - 1, 1);
		}
		#ifndef ONLINE_JUDGE
			for (int i = 1; i <= n; ++ i) {
				cerr << query(1, n, 1, i, i).max_val << ' ';
			}
			cerr << endl;
		#endif
	}
}