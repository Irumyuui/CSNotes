#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
vector<int> edge[N];
void add(int from, int to) {
	edge[from].push_back(to);
}
int dfn[N], low[N], step = 0;
int n;
int cut = 1 << 30;
int s, t;
void tarjan(int now, int root) {
	dfn[now] = low[now] = ++ step;
	int cnt = 0;
	for (int nex : edge[now]) {
		if (!dfn[nex]) {
			tarjan(nex, root);
			low[now] = min(low[now], low[nex]);
			if (low[nex] >= dfn[now]) {
				cnt ++;
				if ((now != root || cnt >= 2) && now != s && now != t) {
					// cerr << now << endl;
					if (dfn[nex] <= dfn[s] && dfn[nex] > dfn[t] || dfn[nex] <= dfn[t] && dfn[nex] > dfn[s]) {
						cut = min(cut, now);
					}
				}
			}
		} else {
			low[now] = min(low[now], dfn[nex]);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	for (int a, b; cin >> a >> b && (a || b); ) {
		add(a, b);
		add(b, a);
	}
	cin >> s >> t;
	tarjan(1, 1);
	if (cut == 1 << 30) {
		cout << "No solution";
	} else {
		cout << cut;
	}
}