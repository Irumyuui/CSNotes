#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
std::istream& operator >> (std::istream &is, __int128_t &x) {
    x = 0;
    std::string s; is >> s;
    bool flag = false;
    for (auto ch : s) 
        if (ch == '-') flag = true;
        else x = x * 10 + (ch ^ 48);
    if (flag) x = -x;
    return is;
}
std::ostream& operator << (std::ostream &os, __int128_t x) {
    if (x == 0) return os << '0';
    bool flag = false;
    if (x < 0) 
        x = -x, flag = true;
    std::string s;
    while (x > 0)
        s += x % 10 + '0', x /= 10;
    if (flag) s += '-';
    std::reverse(s.begin(), s.end());
    return os << s;
}
using ill = __int128_t;

const int MOD = 10000007;
ill n;
int m, bit[65];
ill f[65][65];

ill dfs(int pos, int bc, bool limit) {
    if (pos > m) {
        return max<ill>(bc, 1);
    }
    if (f[pos][bc] != -1 && !limit) {
        return f[pos][bc];
    }
    ill ret = 1;
    int LIM = limit ? bit[pos] : 1;
    for (int i = 0; i <= LIM; ++ i) {
        if (i == 1) {
            ret *= dfs(pos + 1, bc + 1, i == LIM && limit);
        } else {
            ret *= dfs(pos + 1, bc, i == LIM && limit);
        }
        ret %= MOD;
    }
    if (!limit) {
        f[pos][bc] = ret;
    }
    return ret;
}
ill dfs(ill num) {
    m = 0;
    memset(f, -1, sizeof f);
    while (num > 0) {
        bit[++ m] = num & 1;
        num >>= 1;
    }
    reverse(bit + 1, bit + 1 + m);
    return dfs(1, 0, true);
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    cout << dfs(n);
}