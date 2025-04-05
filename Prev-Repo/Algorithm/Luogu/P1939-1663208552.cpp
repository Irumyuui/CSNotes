#include <bits/stdc++.h>

using namespace std;

template <class T, int R, int C>
struct Matrix {
	std::array<std::array<T, C>, R> mat;
	Matrix() = default;
	auto&& operator [] (const int &id) { return mat[id]; }
	const auto& operator [] (const int &id) const { return mat[id]; }
	template <int M> 
	friend Matrix<T, R, M> operator * (const Matrix<T, R, C> &a, const Matrix<T, C, M> &b) {
		Matrix<T, R, M> ret;
		for (int i = 0; i < R; ++ i)
			for (int j = 0; j < M; ++ j)
				for (int k = 0; k < C; ++ k)
					ret[i][j] += a[i][k] * b[k][j];
		return ret;
	}
	constexpr int r() const { return R; }
	constexpr int c() const { return C; }
};

template <class T, int n>
Matrix<T, n, n> qpow(Matrix<T, n, n> a, long long i) {
	Matrix<T, n, n> ret;
	for (int i = 0; i < n; ++ i) {
		ret[i][i] = 1;
	}
	for (; i > 0; i >>= 1, a = a * a) {
		if (i & 1) ret = ret * a;
	}
	return ret;
}

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

using Mat = Matrix<Modint<int(1e9 + 7)>, 3, 3>;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	while (t --) {
		int n;
		cin >> n;
		if (n <= 3) {
			cout << 1 << '\n';
		} else {
			Mat a, b;
			a[0][0] = a[0][2] = a[1][0] = a[2][1] = 1;
			b[0][0] = b[1][0] = b[2][0] = 1;
			a = qpow(a, n - 3);
			auto ret = a * b;
			cout << ret[0][0] << '\n';
		}
	}
}