/* P1939 【模板】矩阵加速（数列） */
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
	friend std::ostream &operator << (std::ostream &os, const Modint &a) { return os << a.v; }
};

const int MOD = 1e9 + 7;

using mint = Modint<MOD>;
struct Matrix {
	std::vector<std::vector<mint>> mt;
	int r, c;
	Matrix(int r, int c) : r(r), c(c), mt(r, std::vector<mint>(c)) {}
	void clear() { for (auto &x : mt) fill(x.begin(), x.end(), mint(0)); }
	void basic() { clear(); for (int i = 0; i < min(r, c); ++ i) mt[i][i] = 1; }
	std::vector<mint> &operator [] (int id) noexcept { return mt[id]; }
	const std::vector<mint> &operator [] (const int id) const noexcept { return mt[id]; }
	friend Matrix operator * (const Matrix &a, const Matrix &b) {
		Matrix ret(a.r, b.c);
		for (int i = 0; i < a.r; ++ i) {
			for (int j = 0; j < b.c; ++ j) {
				for (int k = 0; k < a.r; ++ k) {
					ret[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		return ret;
	}
	friend Matrix operator ^ (Matrix a, int64_t i) {
		Matrix ret(a.r, a.c);
		ret.basic();	
		while (i) {
			if (i & 1) {
				ret = ret * a;
			}
			a = a * a;
			i >>= 1;
		}
		return ret;
	}
	const Matrix &operator *= (const Matrix &x) {
		*this = *this * x;
		return *this;
	}
	const Matrix &operator ^= (int64_t i) {
		*this = *this ^ i;
		return *this;
	}
};

void Solution() {
	int n;
	ll k;
	cin >> n >> k;
	Matrix a(n, n);
	for (int i = 0; i < n; ++ i) for (int j = 0; j < n; ++ j) {
		int x;
		cin >> x;
		a[i][j] = mint(x);
	}
	a ^= k;
	for (int i = 0; i < n; ++ i) for (int j = 0; j < n; ++ j) {
		cout << a[i][j] << " \n"[j == n - 1];
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}