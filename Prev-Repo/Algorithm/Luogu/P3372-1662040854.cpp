#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 动态开点 线段树
struct LazySeg {
	/* ============ 定义 ============ */
	struct Info {  // 信息
		ll val;
		Info(const ll &val = 0) : val(val) {}
		friend Info operator + (const Info &a, const Info &b) {  // 区间结合律
			return Info {
				a.val + b.val,
			};
		}
	};
	struct Node {  // 线段树节点
		Info val;
		ll lz_a;  // 懒惰标记（区间加）
		int l, r;  // child
		Node() : val({}), lz_a(0), l(0), r(0) {}
	};
	int n;  // 区间范围：[1, n]
	std::vector<Node> seg;  // 根节点为1
	/* ============ 更新 ============ */
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
	/* ============ 建树 ============ */
	void init(int _n) {
		n = _n;
	}
	void build(const auto &a) {
		static std::function<void(int,int,int)> build = [&](int l, int r, int id) {
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
		seg.push_back({});  // 0号节点
		build(1, n, 1);
	}
	void rebuild(const auto &a) {
		static std::function<void(int,int,int)> build = [&](int l, int r, int id) {
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
	/* ============ 操作 ============ */
	void add(int al, int ar, ll d) {
		static std::function<void(int,int,int,int,int)> add = [&](int l, int r, int id, int al, int ar) {
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
	/* ============ 查询 ============ */
	Info query(int ql, int qr) {
		static std::function<Info(int,int,int,int,int)> query = [&](int l, int r, int id, int ql, int qr) {
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
	}
}