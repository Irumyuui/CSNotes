#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n;
	cin >> n;

	vector<string> a(n);
	for (auto &&s : a) {
		cin >> s;
	}
	ranges::sort(a);

	vector<int> dad(max(n, 26), -1);
	auto Find = [&](auto &&Find, int x) -> int {
		if (dad[x] == -1) {
			return x;
		}
		return dad[x] = Find(Find, dad[x]);
	};
	auto Merge = [&](int a, int b) {
		a = Find(Find, a); b = Find(Find, b);
		if (a == b)
			return false;
		dad[a] = b;
		return true;
	};

	vector<int> deg(26);
	vector<bool> vis(max(n, 26));
	for (auto &x : a) {
		deg[x.front() - 'a'] ++;
		deg[x.back() - 'a'] --;
		Merge(x.front() - 'a', x.back() - 'a');
		vis[x.front() - 'a'] = vis[x.back() - 'a'] = true;
	}

	int dcnt = 0;
	for (int i = 0; i < 26; i ++) {
		if (vis[i]) {
			dcnt += dad[i] == -1;
		}
		cerr << char(i + 'a') << ' ' << dad[i] << '\n';
	}
	if (dcnt != 1) {
		cout << "***\n";
		return;
	}

	int cnt = 0, beg = -1;
	for (int i = 0; i < 26; i ++) {
		if (deg[i]) {
			if (abs(deg[i]) > 1) {
				cout << "***\n";
				return;
			} else {
				cnt ++;
			}
			if (deg[i] == 1) {
				if (beg == -1) {
					beg = i;
				} else {
					cout << "***\n";
					return;
				}
			}
		}
	}
	if (cnt != 0 && cnt != 2) {
		cout << "***\n";
		return;
	}

	vector adj(n, vector<int>());
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < n; j ++) {
			if (i != j && a[i].back() == a[j].front()) {
				adj[i].emplace_back(j);
			}
		}
	}
	
	fill(vis.begin(), vis.end(), false);
	vector<int> ret;
	auto dfs = [&](auto &&dfs, int from) -> void {
		if (vis[from])
			return;
		vis[from] = true;
		for (auto to : adj[from]) {
			if (!vis[to]) {
				dfs(dfs, to);
			}
		}
		ret.emplace_back(from);
	};
	for (int i = 0; i < n; i ++) {
		if (beg != -1) {
			if (a[i].front() - 'a' == beg) {
				dfs(dfs, i);
				// break;
			}
		} else {
			dfs(dfs, i);
			// break;
		}
	}

	ranges::reverse(ret);
	assert(ret.size() == n);
	for (int i = 0; i < ret.size(); i ++) {
		if (i == 0) {
			cout << a[ret[i]];
		} else {
			cout << "." << a[ret[i]];
		}
	}
	cout << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}