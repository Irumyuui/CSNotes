#include <bits/stdc++.h>

using namespace std;
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m, r;
	cin >> n;
	vector<array<int,3>> info(n);
	for (auto &[a, b, c] : info) {
		cin >> a >> b >> c;
	}
	cin >> m >> r;
	vector ft(m + 1, vector<int>(r + 1, 0)), fc(ft);
	for (auto [a, b, c] : info) {
		for (int j = m; j >= a; -- j) {
			for (int k = r; k >= b; -- k) {
				if (fc[j - a][k - b] + 1 > fc[j][k]) {
					fc[j][k] = fc[j - a][k - b] + 1;
					ft[j][k] = ft[j - a][k - b] + c;
				} else if (fc[j - a][k - b] + 1 == fc[j][k]) {
					ft[j][k] = min(ft[j][k], ft[j - a][k - b] + c);
				}
			}
		}
	}
	cout << ft[m][r];
}