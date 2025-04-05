#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ill = __int128_t;

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

const int N = 81;
ill f[N][N][N]{};
int a[N][N];
int n, m;
ill pow2[N];

ill dfs(int l, int r, int line, int icnt) {
	if (l == r) {
		return f[l][r][icnt] = a[line][l] * pow2[icnt]; 
	} else if (f[l][r][icnt] != -1) {
		return f[l][r][icnt];
	}
	f[l][r][icnt] = max({
		dfs(l + 1, r, line, icnt + 1) + a[line][l] * pow2[icnt],
		dfs(l, r - 1, line, icnt + 1) + a[line][r] * pow2[icnt]
	});
	return f[l][r][icnt];
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	pow2[0] = 1;
	for (int i = 1; i < N; ++ i) {
		pow2[i] = pow2[i - 1] * 2;
	}
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) for (int j = 1; j <= m; ++ j) {
		cin >> a[i][j];
	}
	ill ans = 0;
	for (int i = 1; i <= n; ++ i) {
		memset(f, -1, sizeof f);
		ans += dfs(1, m, i, 1);
	}
	cout << ans;
}