#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct LazySeg {
	struct Info {
		ll val;
		friend Info operator + (const Info &a, const Info &b) {
			return Info {
				a.val + b.val,
			};
		}
	};
	struct Node {
		Info val;
		ll lz_a;
		int l, r;  // child
		Node() : val({}), lz_a(0), l(0), r(0) {}
	};
	int n;
	std::vector<Node> seg;
	void update(int l, int r, int id, ll d) {
		seg[id].val.val += (r - l + 1) * d;
		seg[id].lz_a += d;
	}
	void rise(int id) {
		seg[id].val = seg[seg[id].l].val + seg[seg[id].r].val;
	}
	void down(int l, int r, int id) {
		if (l == r) return;
		auto &d = seg[id].lz_a;
		if (d == 0) return;
		int mid = l + ((r - l) >> 1);
		update(l, mid, seg[id].l, d);
		update(mid + 1, r, seg[id].r, d);
		d = 0;
	}
	void init(int _n) {
		n = _n;
	}
	void build(const auto &a) {
		std::function<void(int,int,int)> build = [&](int l, int r, int id) {
			seg.push_back({});
			if (l == r) {
				seg[id].val = {a[l]};
			} else {
				int mid = l + ((r - l) >> 1);
				seg[id].l = seg.size();
				build(l, mid, seg[id].l);
				seg[id].r = seg.size();
				build(mid + 1, r, seg[id].r);
				rise(id);
			}
		};
		seg.clear();
		seg.push_back({});
		build(1, n, 1);
	}
	void rebuild(const auto &a) {
		std::function<void(int,int,int)> build = [&](int l, int r, int id) {
			if (l == r) {
				seg[id].val = {a[l]};
			} else {
				int mid = l + ((r - l) >> 1);
				build(l, mid, seg[id].l);
				build(mid + 1, r, seg[id].r);
				rise(id);
			}
		};
		build(1, n, 1);
	}
	void init(int _n, const auto &a) {
		init(_n);
		build(a);
	}
	void add(int al, int ar, ll d) {
		std::function<void(int,int,int,int,int)> add = [&](int l, int r, int id, int al, int ar) {
			if (l == al && r == ar) {
				update(l, r, id, d);
			} else {
				int mid = l + ((r - l) >> 1);
				down(l, r, id);
				if (ar <= mid) {
					add(l, mid, seg[id].l, al, ar);
				} else if (al > mid) {
					add(mid + 1, r, seg[id].r, al, ar);
				} else {
					add(l, mid, seg[id].l, al, mid);
					add(mid + 1, r, seg[id].r, mid + 1, ar);
				}
				rise(id);
			}
		};
		add(1, n, 1, al, ar);
	}
	Info query(int ql, int qr) {
		std::function<Info(int,int,int,int,int)> query = [&](int l, int r, int id, int ql, int qr) {
			if (l == ql && r == qr) {
				return seg[id].val;
			} else {
				int mid = l + ((r - l) >> 1);
				down(l, r, id);
				if (qr <= mid) {
					return query(l, mid, seg[id].l, ql, qr);
				} else if (ql > mid) {
					return query(mid + 1, r, seg[id].r, ql, qr);
				} else {
					return query(l, mid, seg[id].l, ql, mid) + query(mid + 1, r, seg[id].r, mid + 1, qr);
				}
			}
		};
		return query(1, n, 1, ql, qr);
	}
};

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, q;
	cin >> n >> q;
	vector<ll> a(n + 1);
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	LazySeg seg;
	seg.init(n, a);
	
	#ifndef ONLINE_JUDGE
		for (int i = 1; i <= n; ++ i) {
			cerr << seg.query(i, i).val << ' ';
		}
		cerr << '\n';
	#endif

	while (q --) {
		int opt, l, r;
		cin >> opt >> l >> r;
		if (opt == 1) {
			ll k;
			cin >> k;
			seg.add(l, r, k);
		} else {
			cout << seg.query(l, r).val << '\n';
		}

		#ifndef ONLINE_JUDGE
			for (int i = 1; i <= n; ++ i) {
				cerr << seg.query(i, i).val << ' ';
			}
			cerr << '\n';
		#endif
	}
}