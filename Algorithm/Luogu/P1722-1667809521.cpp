#include <bits/stdc++.h>

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
	friend std::ostream & operator << (std::ostream &out, const Modint &x) { out << x.v; return out; }
};
using mint = Modint<100>;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	std::cin >> n;
	std::vector<mint> f(n + 1);
	f[0]=f[1]=1;
	for (int i = 2; i <= n; i ++) {
		for (int j = 1; j <= i; j ++) {
			f[i] += f[j - 1] * f[i - j];
		}
	}
	std::cout << f[n] << '\n';
}