#include <bits/stdc++.h>
using namespace std;
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
using ll = long long;

ill n;
ill f[10];
int d[20], m;
ill pw[19];

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	pw[0] = 1;
	for (int i = 1; i <= 18; ++ i) {
		pw[i] = pw[i - 1] * 10;
	}
	cin >> n;
	while (n > 0) {
		d[++ m] = n % 10;
		n /= 10;
	}
	reverse(d + 1, d + 1 + m);
	for (int i = 1; i <= m; ++ i) {
		f[d[i]] ++;
		for (int j = 1; j < i; ++ j) {
			f[d[j]] += d[i] * pw[m - i];
		}
		for (int j = 1; j < d[i]; ++ j) {
			f[j] += pw[m - i];
		}
		if (i != m && d[i]) {
			for (int j = 1; j <= 9; ++ j) {
				f[j] += d[i] * (m - i) * pw[m - i - 1];
			}
		}
	}
	ill ans = 0;
	for (int i = 1; i <= 9; ++ i) {
		ans += f[i] * i;
	}
	cout << ans;
}