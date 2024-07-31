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

const int MOD = 1e9 + 7;
ill pre[20];
ill f[10];
int di[20];

void solve(ill num, int der) {
	int m = 0;
	memset(di, 0, sizeof di);
	while (num > 0) {
		di[++ m] = num % 10;
		num /= 10;
		f[di[m]] += der;
	}
	reverse(di + 1, di + 1 + m);
	for (int i = 1; i <= m; ++ i) {
		for (int j = 1; j < i; ++ j) {
			f[di[j]] += di[i] * pre[m - i] * der;
		}
		for (int j = 1; j < di[i]; ++ j) {
			f[j] += pre[m - i] * der;
		}
		if (i != m && di[i]) {
			for (int j = 1; j <= 9; ++ j) {
				f[j] += (m - i) * di[i] * pre[m - i - 1] * der;
			}
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	pre[0] = 1;
	for (int i = 1; i < 20; ++ i) {
		pre[i] = pre[i - 1] * 10;
	}
	int t;
	cin >> t;
	while (t --) {
		ill l, r;
		cin >> l >> r;
		memset(f, 0, sizeof f);
		solve(r, 1);
		solve(l - 1, -1);
		ill ans = 0;
		for (int i = 1; i <= 9; ++ i) {
			ans = (ans + f[i] * i % MOD) % MOD;
		}
		cout << ans << endl;
	}
}