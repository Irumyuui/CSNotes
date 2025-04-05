#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<pair<int,double>> edge[N];
double f[N];
int ind[N], iind[N];
void add_edge(int from, int to, double w) {
	edge[from].emplace_back(to, w);
	edge[to].emplace_back(from, w);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(2);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i ++) {
		int a, b;
		double w;
		cin >> a >> b >> w;
		add_edge(b, a, w);
		ind[a] ++;
		iind[a] ++;
	}
	queue<int> q;
	q.push(n);
	while (!q.empty()) {
		int from = q.front(); q.pop();
		for (auto [to, w] : edge[from]) {
			f[to] += (f[from] + w) / iind[to];
			if (-- ind[to] == 0) {
				q.push(to);
			}
		}
	}
	cout << f[1] << '\n';
}