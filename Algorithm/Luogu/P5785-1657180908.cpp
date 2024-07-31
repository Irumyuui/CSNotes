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
		int L = l, R = r;
		while (L < R) {
			// int mid = l + r >> 1;
			// int mid = l + ((r - l) >> 1);
			int mid = L + ((R - L) >> 1);
			// if (f[q[mid]] - f[q[mid + 1]] >= (t[i] + s) * (c[q[mid]] - c[q[mid + 1]])) {
			if (f[q[mid + 1]] - f[q[mid]] > (t[i] + s) * (c[q[mid + 1]] - c[q[mid]])) {
				// tag = mid;
				R = mid;
			} else {
				L = mid + 1;
			}
		}
		f[i] = f[q[R]] - (t[i] + s) * c[q[R]] + t[i] * c[i] + s * c[n];
		while (
			l < r && (f[q[r]] - f[q[r - 1]]) * (c[i] - c[q[r]]) >= (f[i] - f[q[r]]) * (c[q[r]] - c[q[r - 1]])
			) {
			r --;
		}
		q[++ r] = i;
	}
	cout << f[n];
}