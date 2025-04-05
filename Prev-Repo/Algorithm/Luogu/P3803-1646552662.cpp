#include <bits/stdc++.h>
using namespace std;
using Complex = complex<double>;

const double PI = acos(-1);
void fft(vector<Complex>&a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++ i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) 
            j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double k = 2 * PI / len * (inv ? 1 : -1);
        Complex wn(cos(k), sin(k));
        for (int i = 0; i < n; i += len) {
            Complex wk(1);
            for (int j = 0; j < len / 2; j ++) {
                Complex x = a[i + j], y = a[i + j + len / 2] * wk;
                a[i + j] = x + y;
                a[i + j + len / 2] = x - y;
                wk *= wn;
            }
        }
    }
    if (inv) 
        for (auto &x : a)
            x /= n;
}
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    int len = 1;
    while (len <= n + m) len <<= 1;
    vector<Complex>a(len, Complex(0)), b(len, Complex(0)), c(len, Complex(0));
    for (int i = 0; i <= n; ++ i) {
        int x; cin >> x;
        a[i].real(x);
    }
    for (int i = 0; i <= m; ++ i) {
        int x; cin >> x;
        b[i].real(x);
    }

    fft(a, false); fft(b, false);
    for (int i = 0; i < len; ++ i) 
        c[i] = a[i] * b[i];
    fft(c, true);

    for (int i = 0; i <= m + n; ++ i) {
        int ans = c[i].real() + 0.5;
        cout << ans << ' ';
    }

    return 0;
}