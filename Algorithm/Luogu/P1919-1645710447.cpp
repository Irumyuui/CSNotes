#include <bits/stdc++.h>
using namespace std;
#define all(X) begin(X), end(X)
#define cauto const auto

using ll = long long;
using LL = __int128_t;

namespace FFT_t {

    struct Complex {
        double x, y;
        Complex() : x(0), y(0) {}
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
    };

    const double __PI_ = std::acos(-1.0);
    const int __MAXN_ = 5e6 + 10;

    int __R[__MAXN_];

    // bufferfly operation
    inline void bopt(int len, int bit) {
        for (int i = 0; i < len; ++ i) {
            __R[i] = (__R[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        }
    }

    // flag: 1 FFT -1 IFFT
    // Alen : Length of the target polynomial A
    void FFT(Complex *A, int Alen, int flag) {
        for (int i = 0; i < Alen; ++ i) {
            if (i < __R[i]) {
                std::swap(A[i], A[__R[i]]);
            }
        }
        for (int mid = 1; mid < Alen; mid <<= 1) {
            const Complex Wn(std::cos(__PI_ / mid), flag * std::sin(__PI_ / mid));
            
            for (int pos = 0, len = mid << 1; pos < Alen; pos += len) {
                Complex wk(1, 0);
                
                for (int k = 0; k < mid; ++ k, wk = wk * Wn) {
                    Complex fir = A[pos + k], sec = A[pos + k + mid] * wk;
                    A[pos + k] = fir + sec;
                    A[pos + k + mid] = fir - sec;
                }
            }
        }

        // is IFFT
        if (flag == -1) {
            for (int i = 0; i < Alen; ++ i) {
                A[i].x /= Alen;
            }
        }
    }
    
}

using namespace FFT_t;

const int MAXN = 5e6 + 10;
Complex a[MAXN], b[MAXN];
int ans[MAXN];

void pre(int &len, string &num, Complex *A) {
    len = -1;

    for (int i = num.size() - 1; i >= 0; -- i) {
        A[++ len].x = int(num[i] - '0');
    }
    
    if (len < 0) {
        len = 0;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    string anum, bnum;

    cin >> anum >> bnum;

    int n, m;
    pre(n, anum, a);
    pre(m, bnum, b);


    int len = 1, bit = 0;
    while (len <= n + m) {
        len <<= 1; bit ++;
    }

    bopt(len, bit);

    FFT(a, len, 1); FFT(b, len, 1);

    for (int i = 0; i < len; ++ i) {
        a[i] = a[i] * b[i];
    }

    FFT(a, len, -1);

    int lim = m + n;

    for (int i = 0; i <= lim; ++ i) {
        ans[i] += int(a[i].x + 0.5);
        
        if (ans[i] >= 10) {
            ans[i + 1] += ans[i] / 10;
            ans[i] %= 10;
            if (i == lim) {
                lim ++;
            }
        }
    }

    bool flag = false;
    
    for (int i = lim; i >= 0; -- i) {
        if (ans[i]) 
            flag = true;
        if (flag)
            cout << ans[i];
    }

    if (flag == false) {
        cout << 0;
    }

    return 0;
}