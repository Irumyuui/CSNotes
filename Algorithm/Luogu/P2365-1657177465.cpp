#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 10;
int n, s;
ll f[N], t[N], c[N];
int q[N], l, r;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> s;
	for (int i = 1; i <= n; ++ i) {
		cin >> t[i] >> c[i];
		t[i] += t[i - 1];
		c[i] += c[i - 1];
	}
	l = r = 1;
	for (int i = 1; i <= n; ++ i) {
		while (
			l < r && f[q[l]] - f[q[l + 1]] >= (t[i] + s) * (c[q[l]] - c[q[l + 1]])
			) {
			l ++;
		}
		f[i] = f[q[l]] - (t[i] + s) * c[q[l]] + t[i] * c[i] + s * c[n];
		while (
			l < r && (f[q[r]] - f[q[r - 1]]) * (c[i] - c[q[r]]) >= (f[i] - f[q[r]]) * (c[q[r]] - c[q[r - 1]])
			) {
			r --;
		}
		q[++ r] = i;
	}
	cout << f[n];
}

