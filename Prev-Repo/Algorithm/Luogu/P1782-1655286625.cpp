#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int f[N];
int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m, C;
	cin >> n >> m >> C;
	for (int i = 1; i <= n; ++ i) {
		int vi, wi, d;
		cin >> vi >> wi >> d;
		for (int k = 1; k <= d; k <<= 1) {
			d -= k;
			int v = vi * k, w = wi * k;
			for (int j = C; j >= v; -- j) {
				f[j] = max(f[j], f[j - v] + w);
			}
		}
		if (d > 0) {
			int v = vi * d, w = wi * d;
			for (int j = C; j >= v; -- j) {
				f[j] = max(f[j], f[j - v] + w);
			}
		}
	}
	for (int i = 1; i <= m; ++ i) {
		int a, b, c;
		cin >> a >> b >> c;
		for (int j = C; j >= 0; -- j) {
			for (int k = 0; k <= j; ++ k) {
				int v = a * k * k + b * k + c, w = k;
				f[j] = max(f[j], f[j - w] + v);
			}
		}
	}
	cout << f[C] << '\n';
}