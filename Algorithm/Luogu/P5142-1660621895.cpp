/* P5142 区间方差 */
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

template <int _P>
struct Modint {
	using ll = int64_t;
	static constexpr int P = _P;
	int v;
	Modint() : v(0) {}
	Modint(ll _v) { v = _v % P; if (v < 0)v += P; }
	explicit operator int() const { return v; }
	explicit operator long long() const { return v; }
	explicit operator bool() const { return v > 0; }
	bool operator == (const Modint &o) const { return v == o.v; }
	bool operator != (const Modint &o) const { return v != o.v; }
	Modint operator - () const { return Modint(v ? P - v : 0); }
	Modint operator + () const { return *this; }
	Modint & operator ++ () { v++; if (v == P)v = 0; return *this; }
	Modint & operator -- () { if (v == 0)v = P; v--; return *this; }
	Modint operator ++ (int) { Modint r = *this; ++*this; return r; }
	Modint operator -- (int) { Modint r = *this; --*this; return r; }
	Modint & operator += (const Modint &o) { v += o.v; if (v >= P)v -= P; return *this; }
	Modint operator + (const Modint & o)const { return Modint(*this) += o; }
	Modint & operator -= (const Modint & o) { v -= o.v; if (v < 0)v += P; return *this; }
	Modint operator - (const Modint &o)const { return Modint(*this) -= o; }
	Modint & operator *=(const Modint & o) { v = (int)(((ll)v)*o.v%P); return *this; }
	Modint operator * (const Modint & o)const { return Modint(*this) *= o; }
	Modint & operator /= (const Modint & o) { return (*this) *= o.Inv(); }
	Modint operator / (const Modint & o)const { return Modint(*this) /= o; }
	friend Modint operator + (const Modint &x, const ll &o) { return x + (Modint)o; }
	friend Modint operator + (const ll &o, const Modint &x) { return x + (Modint)o; }
	friend Modint operator - (const Modint &x, const ll &o) { return x - (Modint)o; }
	friend Modint operator - (const ll &o, const Modint &x) { return (Modint)o - x; }
	friend Modint operator * (const Modint &x, const ll &o) { return x * (Modint)o; }
	friend Modint operator * (const ll &o, const Modint &x) { return x * (Modint)o; }
	friend Modint operator / (const Modint &x, const ll &o) { Modint c = o; return x * c.Inv(); }
	friend Modint operator / (const ll &o, const Modint &x) { Modint c = o; return c * x.Inv(); }
	Modint operator ^ (ll o)const { Modint r = 1, t = v; while (o) { if (o & 1)r *= t; t *= t; o >>= 1; }return r; }
	Modint operator ~ () { return (*this) ^ (P - 2); }
	Modint Inv() const { return (*this) ^ (P - 2); }
	friend std::istream & operator >> (std::istream &in, Modint &x) { ll d; in >> d; x = d; return in; }
	friend std::ostream & operator << (std::ostream &out, Modint &x) { out << x.v; return out; }
};

const int MOD = 1e9 + 7;
using mint = Modint<MOD>;

const int N = 1e5 + 10;

struct Info {
	mint val, pval;
	friend Info operator + (const Info &a, const Info &b) {
		return Info{a.val + b.val, a.pval + b.pval};
	}
} seg[N << 2];

mint a[N];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
	seg[id].pval = seg[id * 2].pval + seg[id * 2 + 1].pval;
}

void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val = a[l];
		seg[id].pval = a[l]  ^ 2;
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void change(int l, int r, int id, int tag, mint val) {
	if (l == r) {
		seg[id].val = val;
		seg[id].pval = val ^ 2;
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) {
			change(l, mid, id * 2, tag, val);
		} else {
			change(mid + 1, r, id * 2 + 1, tag, val);
		}
		rise(id);
	}
}

Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id];
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
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	build(1, n, 1);



	while (m --) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int tag;
			mint y;
			cin >> tag >> y;
			change(1, n, 1, tag, y);
		} else {
			int l, r;
			cin >> l >> r;
			auto [sum, psum] = query(1, n, 1, l, r);
			auto ave = sum / (r - l + 1);
			auto ans = psum / (r - l + 1) - ave * ave;
			cout << ans << '\n';
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}