#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

const int N = 4e5 + 10;
std::vector<int> edge[N];
void adde(int from, int to) {
	edge[from].push_back(to);
}
bool del[N];
int ans[N];
int id[N];
int dad[N];
int cnt, n, m, l;
int Find(int u) {
	if (dad[u] != -1) {
		return dad[u] = Find(dad[u]);
	}
	return u;
}
bool Union(int a, int b) {
	a = Find(a), b = Find(b);
	if (a == b) {
		return false;
	}
	dad[a] = b;
	cnt --;
	return true;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	memset(dad, -1, sizeof dad);
	cin >> n >> m;
	for (int i = 0; i < m; ++ i) {
		int a, b;
		cin >> a >> b;
		adde(a, b);
		adde(b, a);
	}
	cnt = n;
	int q;
	cin >> q;
	for (int i = 1; i <= q; ++ i) {
		int x;
		cin >> x;
		id[i] = x;
		del[x] = true;
	}
	for (int i = 0; i < n; ++ i) {
		if (!del[i]) {
			for (auto j : edge[i]) {
				if (!del[j]) {
					Union(i, j);
				}
			}
		}
	}
	vector<int> ans;
	ans.push_back(cnt - q);
	for (int i = q; i >= 1; -- i) {
		del[id[i]] = false;
		for (auto j : edge[id[i]]) {
			if (!del[j]) {
				Union(j, id[i]);
			}
		}
		ans.push_back(cnt - i + 1);
	}
	reverse(ans.begin(), ans.end());
	for (auto q : ans) {
		cout << q << endl;
	}
}