#include <bits/stdc++.h>
using namespace std;
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = long long;

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
template <typename T, std::size_t _N>
struct Matrix {
    using Value_type = T;
    using Floor = std::array<Value_type, _N>;
    using Mat = std::array<Floor, _N>;
    using _Matrix = Matrix<Value_type, _N>;
    static constexpr std::size_t N = _N;
    Mat mat;
    Floor& operator [] (int _r) {
        return mat[_r];
    }
    const Floor& operator [] (int _r) const {
        return mat[_r];
    }
    Value_type& operator () (int _r, int _c) {
        return mat[_r][_c];
    }
    const Value_type& operator () (int _r, int _c) const {
        return mat[_r][_c];
    }
    template <typename ...Value_type_page>
    void init(const Value_type_page&... init_list) {
        constexpr int last = sizeof...(init_list) - 1;
        int r{}, c{};
        ((r * N + c < last && (r * N + c < N * N) ? (mat[r][c] = init_list) : (mat[r][c] = init_list), (c + 1 >= N ? (r ++, c = 0) : (c ++))), ...);
    }
    Matrix() : mat{} {}
    template <typename ...Value_type>
    Matrix(const Value_type &...init_list) {
        init(init_list...);
    }
    friend _Matrix operator * (const _Matrix &a, const _Matrix &b) {
        _Matrix ret({});
        for (int i{}; i < N; i ++) {
            for (int k{}; k < N; k ++) {
                const auto &r = a[i][k];
                for (int j{}; j < N; j ++) {
                    ret[i][j] += r * b[k][j];
                }
            }
        }
        return ret;
    }
    _Matrix& operator *= (const _Matrix &a) {
        return (*this) = (*this) * a;
    }
    friend _Matrix operator + (const _Matrix &a, const _Matrix &b) {
        Matrix ret({});
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < N; j ++) {
                ret[i][j] = a[i][j] + b[i][j];
            }
        }
        return ret;
    }
    _Matrix& operator += (const _Matrix &a) {
        (*this) = (*this) + a;
        return *this;
    }
    friend _Matrix operator ^ (_Matrix a, long long i) {
        _Matrix ret;
        for (int i = 0; i < N; i ++) {
            ret[i][i] = T(1);
        }
        for (; i; i >>= 1, a *= a) {
            if (i & 1) {
                ret *= a;
            }
        }
        return ret;
    }
    _Matrix& operator ^= (long long i) {
        (*this) = (*this) ^ i;
        return *this;
    }
    void swap(_Matrix &x) {
        std::swap(this->mat, x.mat);
    }
};
using Mat = Matrix<Modint<int(1e9+7)>,3>;

void Solve() {
    int n;
    cin >> n;
    if (n <= 3) {
        cout << 1 << '\n';
    } else {
        Mat a({
            1, 0, 1,
            1, 0, 0,
            0, 1, 0,
        }), b({
            1, 0, 0,
            1, 0, 0,
            1, 0, 0
        });
        cout << ((a ^ (n - 3)) * b)[0][0] << '\n';
    }
}

int32_t main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(12);
    int t = 1;
    std::cin >> t;
    for (int rp = 1; t --> 0; rp ++) {
        Solve();
    }
}