/* P4145 上帝造题的七分钟 2 花神游历各国 */
#include <bits/stdc++.h>
using namespace std;

#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

const int N = 1e6 + 10;
struct Info {
	ll val, max_val;
	void init(ll x) {
		val = max_val = x;
	}
	friend Info operator + (const Info &a, const Info &b) {
		return Info {
			a.val + b.val,
			max(a.max_val, b.max_val),
		};
	}
};

struct Node {
	Info val;
} seg[ N << 2];
ll a[N];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
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

void modify(int l, int r, int id, int ml, int mr) {
	if (seg[id].val.max_val <= 1) {
		return;
	}
	if (l == r) {
		if (seg[id].val.max_val > 1) {
			seg[id].val.init(sqrt(seg[id].val.val));
		}
	} else if (l == ml && r == mr) {
		if (seg[id].val.max_val > 1) {
			int mid = l + ((r - l) >> 1);
			if (seg[id * 2].val.max_val > 1) {
				modify(l, mid, id * 2, ml, mid);
			}
			if (seg[id * 2 + 1].val.max_val > 1) {
				modify(mid + 1, r, id * 2 + 1, mid + 1, mr);
			}
			rise(id);
		}
	} else {
		int mid = l + ((r - l) >> 1);
		if (mr <= mid) {
			modify(l, mid, id * 2, ml, mr);
		} else if (ml > mid) {
			modify(mid + 1, r, id * 2 + 1, ml, mr);
		} else {
			modify(l, mid, id * 2, ml, mid); modify(mid + 1, r, id * 2 + 1, mid + 1, mr);
		}
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
		if (l > r) { swap(l, r); }
		if (opt == 0) {
			modify(1, n, 1, l, r);
		} else {
			cout << query(1, n, 1, l, r).val << '\n';
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	Solution();
}