/* P4588 [TJOI2018]数学计算 */
#include <bits/stdc++.h>
using namespace std;

#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

const int N = 1e5 + 10;
ll mul(ll a, ll b, ll p) {
	a %= p, b %= p;
	ll d = static_cast<long double>(a) * b / p;
	d = a * b - d * p;
	if (d < 0) d += p;
	if (d >= p) d -= p;
	return d;
}
int mod;
struct Info {
	ll val;
	void init(ll d) {
		val = d;
	}
	friend Info operator + (const Info &a, const Info &b) {
		return Info {
			mul(a.val, b.val, mod)
		};
	}
};
struct Node {
	Info val;
} seg[N << 2];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val.init(1);
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void change(int l, int r, int id, int tag, ll d) {
	if (l == r) {
		seg[id].val.init(d);
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) {
			change(l, mid, id * 2, tag, d);
		} else {
			change(mid + 1, r, id * 2 + 1, tag, d);
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
	cin >> n >> mod;
	build(1, n, 1);
	for (int i = 1; i <= n; ++ i) {
		int opt, x;
		cin >> opt >> x;
		if (opt == 1) {
			change(1, n, 1, i, x);
		} else {
			change(1, n, 1, x, 1);
		}
		cout << query(1, n, 1, 1, n).val << '\n';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	int t;
	cin >> t;
	while (t --)
		Solution();
}