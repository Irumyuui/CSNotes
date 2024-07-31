#include <bits/stdc++.h>
using namespace std;

template <int _P>
struct Modint {
	using ll = int64_t;
	static constexpr int P = _P;
	int v;
	constexpr Modint() : v(0) {}
	constexpr Modint(ll _v) { v = _v % P; if (v < 0)v += P; }
	explicit constexpr operator int() const { return v; }
	explicit constexpr operator long long() const { return v; }
	explicit constexpr operator bool() const { return v > 0; }
	constexpr bool operator == (const Modint &o) const { return v == o.v; }
	constexpr bool operator != (const Modint &o) const { return v != o.v; }
	constexpr Modint operator - () const { return Modint(v ? P - v : 0); }
	constexpr Modint operator + () const { return *this; }
	constexpr Modint & operator ++ () { v++; if (v == P)v = 0; return *this; }
	constexpr Modint & operator -- () { if (v == 0)v = P; v--; return *this; }
	constexpr Modint operator ++ (int) { Modint r = *this; ++*this; return r; }
	constexpr Modint operator -- (int) { Modint r = *this; --*this; return r; }
	constexpr Modint & operator += (const Modint &o) { v += o.v; if (v >= P)v -= P; return *this; }
	constexpr Modint operator + (const Modint & o)const { return Modint(*this) += o; }
	constexpr Modint & operator -= (const Modint & o) { v -= o.v; if (v < 0)v += P; return *this; }
	constexpr Modint operator - (const Modint &o)const { return Modint(*this) -= o; }
	constexpr Modint & operator *=(const Modint & o) { v = (int)(((ll)v)*o.v%P); return *this; }
	constexpr Modint operator * (const Modint & o)const { return Modint(*this) *= o; }
	constexpr Modint & operator /= (const Modint & o) { return (*this) *= o.Inv(); }
	constexpr Modint operator / (const Modint & o)const { return Modint(*this) /= o; }
	friend constexpr Modint operator + (const Modint &x, const ll &o) { return x + (Modint)o; }
	friend constexpr Modint operator + (const ll &o, const Modint &x) { return x + (Modint)o; }
	friend constexpr Modint operator - (const Modint &x, const ll &o) { return x - (Modint)o; }
	friend constexpr Modint operator - (const ll &o, const Modint &x) { return (Modint)o - x; }
	friend constexpr Modint operator * (const Modint &x, const ll &o) { return x * (Modint)o; }
	friend constexpr Modint operator * (const ll &o, const Modint &x) { return x * (Modint)o; }
	friend constexpr Modint operator / (const Modint &x, const ll &o) { Modint c = o; return x * c.Inv(); }
	friend constexpr Modint operator / (const ll &o, const Modint &x) { Modint c = o; return c * x.Inv(); }
	constexpr Modint operator ^ (ll o)const { Modint r = 1, t = v; while (o) { if (o & 1)r *= t; t *= t; o >>= 1; }return r; }
	constexpr Modint operator ~ () { return (*this) ^ (P - 2); }
	constexpr Modint Inv() const { return (*this) ^ (P - 2); }
	friend constexpr std::istream & operator >> (std::istream &in, Modint &x) { ll d; in >> d; x = d; return in; }
	friend constexpr std::ostream & operator << (std::ostream &out, const Modint &x) { out << x.v; return out; }
};
using mint = Modint<int(1e9+7)>;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	vector<mint> frac(n + 1), ifrac(n + 1);
	frac[0] = 1;
	for (int i = 1; i <= n; i ++) {
		frac[i] = frac[i - 1] * i;
	}
	ifrac[n] = 1 / frac[n];
	for (int i = n - 1; i >= 0; i --) {
		ifrac[i] = ifrac[i + 1] * (i + 1);
	}
	
	auto C = [&](int n, int m) {
		return frac[n] * ifrac[m] * ifrac[n - m];
	};

	vector f(n + 1, vector<mint>(n + 1));  // 前i个人 前j道题 的合法方案
	f[1][1] = 1;
	for (int i = 2; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			if (j >= i) {
				f[i][j] = C(j, i) * (mint(i - 1) ^ (j - i)); // 让 i 快乐 从j道题中选i道，剩下j-i任意分配给前i-1个
			}
			// i 不快乐 前i-1快乐
			// 分配i题目数
			for (int k = 0; k <= j; k ++) {
				if (k == i) continue;
				f[i][j] += f[i - 1][j - k] * C(j, k);
			}
		}
	}
	cout << f[n][n] << '\n';
}