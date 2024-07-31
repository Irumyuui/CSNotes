#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

void Main() {
	int n;
	cin >> n;
	
	vector<i64> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
		a[i] ^= a[i - 1];
	}

	i64 ans = 0;
	for (int bit = 0; bit <= 20; bit ++) {
		array<i64,2> cnt{};
		for (int i = 0; i <= n; i ++) {
			cnt[(a[i] >> bit) & 1] ++;
		}
		ans += cnt[0] * cnt[1] * (1 << bit);
	}
	cout << ans << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}