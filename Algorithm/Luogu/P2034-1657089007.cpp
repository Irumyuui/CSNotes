#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<ll> a(n + 1), f(a);
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	deque<int> q;
	q.emplace_back(0);
	for (int i = 1; i <= n; ++ i) {
		while (!q.empty() && q.back() + k + 1 < i) {
			q.pop_back();
		}
		f[i] = f[q.back()] + a[i];
		while (!q.empty() && f[q.front()] >= f[i]) {
			q.pop_front();
		}
		q.emplace_front(i);		
	}
	ll sum = 0, ans = 0;
	for (int i = 1; i <= n; ++ i) {
		sum += a[i];
	}
	for (int i = n; i >= n - k; -- i) {
		ans = max(ans, sum - f[i]);
	}
	cout << ans << '\n';
}