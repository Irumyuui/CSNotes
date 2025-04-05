#include <bits/stdc++.h>

using ll = long long;

void Solve(int m) {
	std::vector<std::pair<int,int>> eds(m);
	int n = 0;
	for (auto &[a, b] : eds) {
		std::cin >> a >> b;
		n = std::max({n, a, b});
	}
	std::vector g(n + 1, std::vector<int>());
	for (auto [a, b] : eds) {
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	
	std::vector<int> dfn(n + 1, -1), low(n + 1, -1);
	std::vector<bool> iscut(n + 1);
	std::vector<std::vector<int>> bcc;
	std::stack<int> st;
	int stamp = 0;
	auto tarjan_dfs = [&](auto &&dfs, int from, bool isroot) -> void {
		dfn[from] = low[from] = ++ stamp;
		st.push(from);
		if (isroot && g[from].empty()) {
			bcc.push_back({from});
			return;
		}
		int cnt{};
		for (auto to : g[from]) {
			if (dfn[to] == -1) {
				dfs(dfs, to, false);
				low[from] = std::min(low[from], low[to]);
				if (low[to] >= dfn[from]) {
					cnt ++;
					if (!isroot || cnt >= 2) {
						iscut[from] = true;
					}
					int now = 0;
					bcc.push_back({from});
					do {
						now = st.top();
						st.pop();
						bcc.back().push_back(now);
					} while (now != to);
				}
			} else {
				low[from] = std::min(low[from], dfn[to]);
			}
		}
	};
	for (int i = 1; i <= n; i ++) {
		if (dfn[i] == -1) {
			tarjan_dfs(tarjan_dfs, i, true);
		}
	}

	if (bcc.size() == 1) {
		std::cout << 2 << ' ' << ll(n) * (n - 1) / 2 << '\n';
	} else {
		int ans1 = 0; ll ans2 = 1;
		for (const auto &i : bcc) {
			int cnt = 0;
			for (auto j : i) {
				if (iscut[j]) {
					cnt ++;
				}
			}
			if (cnt == 1) {
				ans1 ++;
				ans2 *= ll(i.size() - 1);
			} else if (cnt == 0) {
				if (i.size() == 1) {
					ans1 ++;
				} else {
					ans1 += 2;
					ans2 *= ll(i.size()) * ll(i.size() - 1) / 2;
				}
			}
		}
		std::cout << ans1 << ' ' << ans2 << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	for (int m, rp = 1; std::cin >> m && m; rp ++) {
		std::cout << "Case " << rp << ": ";
		Solve(m);
	}
}