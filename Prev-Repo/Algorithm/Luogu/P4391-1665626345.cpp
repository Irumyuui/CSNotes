#include <bits/stdc++.h>

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	std::string s;
	std::cin >> n >> s;

	std::vector<int> next(n, -1);
	for (int i = 1, k = -1; i < n; i ++) {
		while (k > -1 && s[k + 1] != s[i]) {
			k = next[k];
		}
		if (s[k + 1] == s[i]) {
			k ++;
		}
		next[i] = k;
	}
	std::cout << n - 1 - next[n - 1] << '\n';
}