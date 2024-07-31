#include <bits/stdc++.h>

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::string a, b;
	std::cin >> a >> b;
	int n = a.size(), m = b.size();
	a = '?' + a; b = '?' + b;
	std::vector<int> bnex(m + 1);
	for (int i = 2, k = 0; i <= m; i ++) {
		while (k && b[k + 1] != b[i]) {
			k = bnex[k];
		}
		if (b[k + 1] == b[i]) {
			k ++;
		}
		bnex[i] = k;
	}
	std::vector<int> ans(n + 1, 0), anex(n + 1);
	int ptr = 0;
	for (int i = 1, k = 0; i <= n; i ++) {
		while (k && b[k + 1] != a[i]) {
			k = bnex[k];
		}
		if (b[k + 1] == a[i]) {
			k ++;
		}
		ans[++ ptr] = i;
		anex[i] = k;
		if (k == m) {
			ptr -= m;
			k = anex[ans[ptr]];
		}
	}
	for (int i = 1; i <= ptr; i ++) {
		std::cout << a[ans[i]];
	}
}