#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	vector<i64> a(n + 1);
	for (int i = 1; i <= n; i ++) 
		cin >> a[i];
	
	vector<int> dad(n + 1, -1);
	auto Find = [&](auto &&Find, int x) -> int {
		if (dad[x] == -1)
			return x;
		return dad[x] = Find(Find, dad[x]);
	};
	auto Merge = [&](int a, int b) -> bool {
		a = Find(Find, a); b = Find(Find, b);
		if (a == b)
			return false;
		if (a > b) swap(a, b);
		dad[b] = a;
		return true;
	};
	for (int i = 2; i <= n; i ++)
		if (a[i - 1] == a[i])
			Merge(i - 1, i);

	priority_queue<pair<i64,int>> q;
	for (int i = 1; i <= n; i ++) {
		if (Find(Find, i) == i) {
			q.emplace(a[i], i);
		}
	}
	int cnt = 0;
	while (!q.empty()) {
		auto now = q.top();
		q.pop();
		if (Find(Find, now.second) != now.second) {
			continue;
		}
		if (now.second - 1 >= 1 && a[Find(Find, now.second - 1)] == a[Find(Find, now.second)]) {
			Merge(now.second - 1, now.second);
			continue;
		}
		if (a[now.second] == 1)
			continue;
		cnt ++;
		a[now.second] = std::sqrt((long double)(a[now.second] / 2 + 1));
		q.emplace(a[now.second], now.second);
	}
	cout << cnt << '\n';
}