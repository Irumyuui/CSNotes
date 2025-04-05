/**
 * @file P2004 领地选择.cpp
 * @author Cieru
 * @date 2022-04-18
 * 
 */

#include <bits/stdc++.h>
using namespace std;

#define all(x) std::begin(x), std::end(x)

namespace __IO_int128 {
    std::istream& operator >> (std::istream &is, __int128_t &x) {
        x = 0;
        std::string s;
        is >> s;
        bool flag = false;
        for (auto ch : s) 
            if (ch == '-')
                flag = true;
            else
                x = x * 10 + (ch ^ 48);
        if (flag) x = -x;
        return is;
    }
    std::ostream& operator << (std::ostream &os, __int128_t x) {
        if (x == 0) return os << '0';
        bool flag = false;
        if (x < 0) {
            x = -x; flag = true;
        }
        std::string s;
        while (x > 0) {
            s += x % 10 + '0'; x /= 10;
        }
        if (flag) s += '-';
        std::reverse(s.begin(), s.end());
        return os << s;
    }
}
namespace __IO_FAST {
    template <class T> inline void read(T &val) {
        T x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -1;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9') {
            x = (x << 1) + (x << 3) + (ch ^ 48);
            ch = getchar();
        }
        val = x * f;
    }
    template <class T> void write(T x) {
        static char a[100];
        if (x == 0) {
            putchar('0');
            return;
        }
        if (x < 0) {
            putchar('-');
            x = -x;
        }
        int cnt = 0;
        while (x) {
            a[++ cnt] = x % 10 + '0';
            x /= 10;
        }
        while (cnt)
            putchar(a[cnt --]);
    }
}
using namespace __IO_FAST;

int main() {    

    int n, m, c;
    read(n), read(m), read(c);

    vector< vector<int> > a(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            read(a[i][j]);
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    int ans = -(1 << 30), ax = 0, ay = 0;
    for (int i = 1; i <= n - c + 1; ++ i) {
        for (int j = 1; j <= m - c + 1; ++ j) {
            int x = i + c - 1, y = j + c - 1;
            if (ans < a[x][y] - a[i - 1][y] - a[x][j - 1] + a[i - 1][j - 1]) {
                ans = a[x][y] - a[i - 1][y] - a[x][j - 1] + a[i - 1][j - 1];
                ax = i, ay = j;
            }
        }
    }
    printf("%d %d", ax, ay);
    
    return 0;
}