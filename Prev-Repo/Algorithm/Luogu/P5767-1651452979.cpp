#include <bits/stdc++.h>
using namespace std;

const int N = 550;
vector<pair<int,int>> g[N];

const int INF = 1 << 30;
bool vis[N];
int dis[N];

void spfa(int sta) {
	fill_n(dis, N, INF);
	fill_n(vis, N, false);

	queue<int> q;
	q.push(sta);
	vis[sta] = true;
	dis[sta] = 0;
	for (; !q.empty(); ) {
		int now = q.front();
		q.pop();
		vis[now] = false;
		for (auto [nex, w] : g[now]) {
			if (dis[nex] > dis[now] + w) {
				dis[nex] = dis[now] + w;
				if (!vis[nex]) {
					vis[nex] = true;
					q.push(nex);
				}
			}
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	
	int n, m;
	cin >> m >> n;

	string s;
	getline(cin, s);
	for (; m --; ) {
		getline(cin, s);
		stringstream ss(s);
		vector<int> v;
		for (int x; ss >> x; ) {
			v.push_back(x);
		}
		for (int i = 0; i < v.size(); ++ i) {
			for (int j = i + 1; j < v.size(); ++ j) {
				auto a = v[i], b = v[j];
				g[a].push_back({b, 1});
			}
		}
	}

	spfa(1);
	if (dis[n] == INF) {
		cout << "NO\n";
	} else {
		cout << dis[n] - 1 << '\n';
	}
}