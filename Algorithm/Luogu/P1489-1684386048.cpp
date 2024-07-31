#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n;
	cin >> n;

	vector<int> cost(n);
	for (auto &x : cost) {
		cin >> x;
	}

	auto tot = reduce(cost.begin(), cost.end());
	// 从前 i 个人中，选择 j 的血量是否可达
	vector f(n / 2 + 1, vector<char>(tot / 2 + 1));
	f[0][0] = 1;
	for (auto c : cost) {
		for (int i = n / 2; i >= 1; i --) {
			for (int j = tot / 2; j >= c; j --) {
				f[i][j] |= f[i - 1][j - c];
			}
		}
	}

	int a = tot, b = 0;
	for (int i = 0; i <= tot / 2; i ++) {
		if (f[n / 2][i] && abs(a - b) > abs(i - (tot - i))) {
			a = i, b = tot - i;
		}
	}
	// cout << a << ' ' << b << '\n';
	cout << min(a, b) << ' ' << max(a, b) << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}