#include <bits/stdc++.h>

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	std::cin >> t;
	while (t --) {
		int n, m;
		std::cin >> n >> m;
		if (n <= m && n > 1) {
			std::cout << "Yes\n";
			continue;
		}
		std::set<int> vis;
		bool ok = false;
		for (int i = 1; i <= m; i ++) {
			if (!vis.count(n % i)) {
				vis.insert(n % i);
			} else {
				ok = true;
				break;
			}
		}
		if (!ok) {
			std::cout << "No\n";
		} else {
			std::cout << "Yes\n";
		}
	}
}