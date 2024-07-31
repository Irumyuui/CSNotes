#include <bits/stdc++.h>

using namespace std;

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
using mint = Modint<int(1e9 + 7)>;

void Main() {
	int n;
	cin >> n;
	if (n <= 3) {
		cout << 1 << '\n';
	} else {
		Matrix<mint,3> a{
			1, 0, 1,
            1, 0, 0,
            0, 1, 0
		}, b{
			1, 0, 0,
            1, 0, 0,
            1, 0, 0
		};
		cout << ((a ^ (n - 3)) * b).at(0,0) << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	while (t --) {
		Main();
	}
}