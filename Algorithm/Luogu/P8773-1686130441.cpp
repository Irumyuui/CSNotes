#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n, q, x;
	cin >> n >> q >> x;

	vector<int> a(n + 1), b(1 << 20);
	for (int i = 1; i <= n; i ++) {
		int t;
		cin >> t;
		int tag = t ^ x;
		a[i] = b[tag];
		b[t] = i;
	}

	vector f(__lg(n) + 1, vector<int>(n + 1));
	f[0] = a;
	for (int i = 1; i <= __lg(n); i ++) {
		for (int j = 1; j + (1 << i) - 1 <= n; j ++) {
			f[i][j] = max(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
		}
	}

	auto Ask = [&](int l, int r) -> int {
		int s = __lg(r - l + 1);
		return max(f[s][l], f[s][r - (1 << s) + 1]);
	};

	for (int _ = 1; _ <= q; _ ++) {
		int l, r;
		cin >> l >> r;
		auto ret = Ask(l, r);
		if (ret >= l) {
			cout << "yes\n";
		} else {
			cout << "no\n";
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}