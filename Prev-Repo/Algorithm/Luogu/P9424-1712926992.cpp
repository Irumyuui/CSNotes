#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

using i64 = int64_t;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;

  std::vector<i64> vw(n);
  for (auto &x : vw) {
    std::cin >> x;
  }

  std::vector adj(n, std::vector<std::pair<int,int>>{});
  std::vector<std::pair<int,int>> edges(m);
  for (int i = 0; i < m; i ++) {
    int u, v;
    std::cin >> u >> v;
    u -= 1; v -= 1;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
    edges[i] = {u, v};
  }

  // std::cerr << 1 << '\n';

  std::vector<int> dfn(n, -1), low(n, -1);
  std::vector<bool> is_bridge(m);
  auto Tarjan = [&, stamp = 0](auto &self, int from, int eid) mutable -> void {
    dfn[from] = low[from] = stamp ++;
    for (auto [to, neid] : adj[from]) {
      if (dfn[to] == -1) {
        self(self, to, neid);
        low[from] = std::min(low[from], low[to]);
      } else if (eid != neid) {
        low[from] = std::min(low[from], dfn[to]);
      }
    }
    if (eid != -1 && dfn[from] == low[from]) {
      is_bridge[eid] = true;
    }
  };
  for (int i = 0; i < n; i ++) {
    if (dfn[i] == -1) {
      Tarjan(Tarjan, i, -1);
    }
  }

  std::vector<int> dsu(n, -1);
  auto Find = [&](auto &self, int from) -> int {
    if (dsu[from] <= -1) {
      return from;
    } else {
      return dsu[from] = self(self, dsu[from]);
    }
  };
  auto MergeTo = [&](int a, int b) {
    // std::cerr << "Merge " << a + 1 << ' ' << b + 1 << '\n';
    a = Find(Find, a);
    b = Find(Find, b);
    if (a == b) {
      return false;
    }
    dsu[b] += dsu[a];
    dsu[a] = b;
    return true;
  };

  for (int u = 0; u < n; u ++) {
    for (auto [v, id] : adj[u]) {
      if (!is_bridge[id]) {
        MergeTo(u, v);
      }
    }
  }
  std::vector<i64> vw_tot(n);
  i64 tot = 0;
  for (int i = 0; i < n; i ++) {
    vw_tot[Find(Find, i)] += vw[i];
    tot += vw[i];
  }


  i64 ans = inf<i64>;
  for (int i = 0; i < m; i ++) {
    if (is_bridge[i]) {
      auto [u, v] = edges[i];
      u = Find(Find, u);
      v = Find(Find, v);
      ans = std::min({ans, std::abs(tot - vw_tot[u] * 2), std::abs(tot - vw_tot[v] * 2)});
    }
  }


  std::cout << ans << '\n';
}
