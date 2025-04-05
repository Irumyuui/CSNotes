#include <bits/stdc++.h>
using namespace std;
#define all(X) begin(X), end(X)
#define cauto const auto

using ll = long long;
using LL = __int128_t;

struct Complex {
    double x, y;
    Complex() = default;
    Complex(const double &x, const double &y) : x(x), y(y) {}
    friend inline Complex operator + (const Complex &a, const Complex &b) {
        return Complex(a.x + b.x, a.y + b.y);
    }
    friend inline Complex operator - (const Complex &a, const Complex &b) {
        return Complex(a.x - b.x, a.y - b.y);
    }
    friend inline Complex operator * (const Complex &a, const Complex &b) {
        return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }
    friend inline bool operator == (const Complex &a, const Complex &b) {
        return a.x == b.x && a.y == b.y;
    }
};

const int MAXN = 1e7 + 10;
const double PI = acos(-1.0);

Complex a[MAXN], b[MAXN], c[MAXN];
int swp[MAXN];

void FFT(int Alen, Complex *A, int flag) {
    for (int i = 0; i < Alen; ++ i) {
        if (i < swp[i]) {
            swap(A[i], A[swp[i]]);
        }
    }

    for (int mid = 1; mid < Alen; mid <<= 1) {
        const Complex Wn(cos(PI / mid), flag * sin(PI / mid));
        for (int len = mid << 1, pos = 0; pos < Alen; pos += len) {
            Complex wk(1, 0);

            for (int k = 0; k < mid; ++ k, wk = wk * Wn) {
                Complex fir = A[pos + k], sec = A[pos + k + mid] * wk;
                A[pos + k] = fir + sec;
                A[pos + k + mid] = fir - sec;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; ++ i) cin >> a[i].x;
    for (int i = 0; i <= m; ++ i) cin >> b[i].x;

    int len = 1, bit = 0;
    while (len <= n + m) {
        len <<= 1; bit ++;
    }

    for (int i = 0; i < len; ++ i) {
        swp[i] = (swp[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    }

    FFT(len, a, 1); FFT(len, b, 1);

    for (int i = 0; i <= len; ++ i) {
        c[i] = a[i] * b[i];
    }

    FFT(len, c, -1);

    for (int i = 0; i <= m + n; ++ i) {
        cout << int(c[i].x / len + 0.5) << ' ';
    }

    return 0;
}