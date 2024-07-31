#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
double cnt[N], money[N];

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;

	for (int i = n - 1; i >= 0; -- i) {
		cnt[i] = (1 + cnt[i + 1] * (1.0 * (n - i) / n) ) / (1 - 1.0 * i / n);
		money[i] = (1 + cnt[i] * (1.0 * i / n) + cnt[i + 1] * (1.0 * (n - i) / n) + money[i + 1] * (1.0 * (n - i) / n))
				/ (1 - (1.0 * i / n));
	}
	cout << fixed << setprecision(2) << money[0];
}