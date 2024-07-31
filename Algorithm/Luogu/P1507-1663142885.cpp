#include <bits/stdc++.h>

using namespace std;
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int m, o;
	cin >> m >> o;
	vector f(m + 1, vector<int>(o + 1, 0));
	int n;
	cin >> n;
	for (int i = 0; i < n; ++ i) {
		int a, b, c;
		cin >> a >> b >> c;
		for (int j = m; j >= a; -- j) {
			for (int k = o; k >= b; -- k) {
				f[j][k] = max(f[j][k], f[j - a][k - b] + c);
			}
		}
	}
	cout << f[m][o] << '\n';
}