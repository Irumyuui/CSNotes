#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include <debug.h>
#else
	#define debug(...)
#endif
using namespace std;
#define cauto const auto
#define all(x) std::begin(x), std::end(x)
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#if __cplusplus >= 202002L
	namespace rgs = ranges;
#endif
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
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
	friend std::ostream & operator << (std::ostream &out, const Modint &x) { out << x.v; return out; }
};
using mint = Modint<2017>;

template <typename Contained, std::size_t Side>
struct Matrix {
	auto &at(std::size_t R, std::size_t C) {
		return data[R * Side + C];
	}
	const auto &at(std::size_t R, std::size_t C) const {
		return data[R * Side + C];
	}
	Matrix operator * (const Matrix &that) const {
		Matrix ret{};
		for (std::size_t i{}; i < Side; i ++)
			for (std::size_t k{}; k < Side; k ++) {
				const Contained &r = (*this).at(i, k);
				for (std::size_t j{}; j < Side; j ++)
					ret.at(i, j) += r * that.at(k, j);
			}
		return ret;
	}
	Matrix &operator *= (const Matrix &that) {
		*this = (*this) * that;
		return *this;
	}
	Matrix operator + (const Matrix &that) const {
		Matrix ret{};
		for (std::size_t i{}; i < Side; i ++)
			for (std::size_t j{}; j < Side; j ++)
					ret.at(i, j) = (*this).at(i, j) + that.at(i, j);
		return ret;
	}
	Matrix &operator += (const Matrix &that) {
		for (std::size_t i{}; i < Side; i ++)
			for (std::size_t j{}; j < Side; j ++)
					(*this).at(i, j) += that.at(i, j);
		return *this;
	}
	Matrix &operator ^= (long long pow_i) {
		Matrix ret{};
		for (std::size_t i{}; i < Side; i ++)
			ret.at(i, i) = 1;
		for (; pow_i > 0; pow_i >>= 1, (*this) *= (*this)) 
			if (pow_i % 2)
				ret *= (*this);
		*this = ret;
		return *this;
	}
	Matrix operator ^ (long long pow_i) const {
		Matrix ret = *this;
		ret ^= pow_i;
		return ret;
	}
	std::array<Contained, Side * Side> data;
};

auto Solve() -> void {
	int n, m;
	cin >> n >> m;

	Matrix<mint, 31> mat;
	for (int i = 0; i <= n; i ++) {
		mat.at(i, 0) = 1;
		mat.at(i, i) = 1;
	}
	for (int i = 0; i < m; i ++) {
		int u, v;
		cin >> u >> v;
		mat.at(u, v) = 1;
		mat.at(v, u) = 1;
	}

	int k;
	cin >> k;
	auto ret = mat ^ k;
	mint ans = 0;
	for (int i = 0; i <= n; i ++) {
		ans += ret.at(1, i);
	}
	cout << ans << '\n';
}

auto main() -> int32_t {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	// std::cin >> tot_test;

	for (int test = 1; test <= tot_test; test += 1) {
		debug(test, "-=-=-=-");
		Solve();
	}
}