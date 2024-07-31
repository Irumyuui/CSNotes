/* P2184 贪婪大陆 */
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

struct LazySeg {
	struct Info {
		int val;
		friend Info operator + (const Info &a, const Info &b) {
			return Info{a.val + b.val};
		}
	};

	struct Node {
		Info val;
		int lz;
	};
	
	int n;
	std::vector<Node> seg;

	void init(int _n) {
		n = _n;
		seg.assign(n << 2, {});
	}

	void rise(int id) {
		seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
	}

	void down(int l, int r, int id) {
		auto &lz = seg[id].lz;
		if (lz == 0) return;
		
		int mid = l + ((r - l) >> 1);
		seg[id * 2].val.val += (mid - l + 1) * lz;
		seg[id * 2 + 1].val.val += (r - mid) * lz;
		seg[id * 2].lz += lz;
		seg[id * 2 + 1].lz += lz;

		lz = 0;
	}

	void add(int al, int ar, int d) {
		add(1, n, 1, al, ar, d);
	}

	void add(int l, int r, int id, int al, int ar, int d) {
		if (l == al && r == ar) {
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
				add(l, mid, id * 2, al, mid, d);
				add(mid + 1, r, id * 2 + 1, mid + 1, ar, d);
			}
			rise(id);
		}
	}

	void add(int tag, int d) {
		add(1, n, 1, tag, d);
	}

	void add(int l, int r, int id, int tag, int d) {
		if (l == r) {
			seg[id].val.val += d;
		} else {
			int mid = l + ((r - l) >> 1);
			down(l, r, id);
			if (tag <= mid) {
				add(l, mid, id * 2, tag, d);
			} else {
				add(mid + 1, r, id * 2 + 1, tag, d);
			}
			rise(id);
		}
	}

	Info query(int ql, int qr) {
		return query(1, n, 1, ql, qr);
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
};

void Solution() {
	int n, m;
	cin >> n >> m;
	LazySeg beg, ed;
	beg.init(n << 2);
	ed.init(n << 2);

	while (m --) {
		int opt, l, r;
		cin >> opt >> l >> r;
		if (opt == 1) {
			beg.add(l, 1);
			ed.add(r, 1);
		} else {
			if (l == 1) {
				cout << beg.query(1, r).val << '\n';
			} else {
				cout << beg.query(1, r).val - ed.query(1, l - 1).val << '\n';
			}
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}