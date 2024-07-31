#include <bits/stdc++.h>
using namespace std;
#pragma region
#ifndef ONLINE_JUDGE
#include <cdebug>
#else
#define debug(...)
#endif
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
#pragma endregion

const int N = 3e5 + 10;
int n, s;
ill t[N], c[N], f[N];
int q[N], hh = 1, tt = 1;

void Solution() {
	cin >> n >> s;
	for (int i = 1; i <= n; ++ i) {
		cin >> t[i] >> c[i];
		t[i] += t[i - 1];
		c[i] += c[i - 1];
	}
	function<int(int,int,ill)> work = [&](int l, int r, ill k) -> int {
		while (l < r) {
			int mid = l + ((r - l) >> 1);
			if (f[q[mid + 1]] - f[q[mid]] >= k * (c[q[mid + 1]] - c[q[mid]])) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}
		return r;
	};
	for (int i = 1; i <= n; ++ i) {
		int p = work(hh, tt, s + t[i]);
		f[i] = f[q[p]] - (t[i] + s) * c[q[p]] + t[i] * c[i] + s * c[n];
		while (hh < tt && (f[q[tt]] - f[q[tt - 1]]) * (c[i] - c[q[tt]]) >= (f[i] - f[q[tt]]) * (c[q[tt]] - c[q[tt - 1]])) {
			tt --;
		}
		q[++ tt] = i;
	}
	cout << f[n];
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}