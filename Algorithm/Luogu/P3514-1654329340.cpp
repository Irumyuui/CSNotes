#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define all(X) std::begin(X), std::end(X)
using ll = long long;

struct info {
	int l, r, val;
};

const int N = 2e6 + 10;
array<int, 2> ans[N];
int a[N], sum[N];

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	fill(all(ans), array<int, 2>{-1, -1});
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	s = ' ' + s;
	for (int i = 1; i <= n; ++ i) {
		a[i] = s[i] == 'T' ? 2 : 1;
		sum[i] = sum[i - 1] + a[i];
		ans[sum[i]] = {1, i};
	}
	for (int i = 2 * n; i >= 2; -- i) {
		auto &[l, r] = ans[i];
		if (l != -1 && r != -1) {
			if (a[l] == 2) {
				ans[i - 2] = {l + 1, r};
			} else if (a[r] == 2) {
				ans[i - 2] = {l, r - 1};
			} else if (a[l] == 1 && a[r] == 1) {
				ans[i - 2] = {l + 1, r - 1};
			}
			if (a[r] == 1) {
				ans[i - 1] = {l, r - 1};
			} else if (a[l] == 1) {
				ans[i - 1] = {l + 1, r};
			}
		}
	}
	while (k --) {
		int x;
		cin >> x;
		auto [l, r] = ans[x];
		if (l != -1) {
			cout << l << ' ' << r << endl;
		} else {
			cout << "NIE" << endl;
		}
	}
}