#include <bits/stdc++.h>
using namespace std;
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, n1, n2;
	cin >> n >> n1 >> n2;
	vector<vector<int>> g(n);
	vector<int> ind(n);
	vector<pair<int,int>> ued(n2);
	for (int i = 0; i < n1; ++ i) {
		int from, to;
		cin >> from >> to;
		from --; to --;
		g[from].push_back(to);
		ind[to] ++;
	}
	for (auto &[a, b] : ued) {
		cin >> a >> b;
	}
	vector<int> dfn(n, inf<int>);
	int stamp = -1;
	queue<int> q;
	for (int i = 0; i < n; ++ i) {
		if (ind[i] == 0) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		dfn[from] = ++ stamp;
		for (auto to : g[from]) {
			if (-- ind[to] == 0) {
				q.push(to);
			}
		}
	}
	for (auto [a, b] : ued) {
		if (dfn[a - 1] < dfn[b - 1]) {
			cout << a << ' ' << b << '\n';
		} else {
			cout << b << ' ' << a << '\n';
		}
	}
}