#include <bits/stdc++.h>

template <typename Capacity>
class MaxFlow {
public:
	explicit MaxFlow(int _n, int _s, int _t, int _reserve_edges = int(1e5 + 10)) 
		: head(_n, -1), cur(_n), lv(_n), s{_s}, t{_t} {
		edge.reserve(_reserve_edges);
	}
	void Reserve(int _size) {
		edge.reserve(_size);
	}
	void Assign(int _n, int _s, int _t) {
		edge.clear();
		head.assign(_n, -1);
		cur.resize(_n);
		lv.resize(_n);
		s = _s;
		t = _t;
	}
	void Clear() {
		std::fill(std::begin(head), std::end(head), -1);
		edge.clear();
	}

	void AddDirectedEdge(int from, int to, const Capacity &cap) {
		AddEdge(from, to, cap);
		AddEdge(to, from, static_cast<Capacity>(0));
	}
	void AddUndirectedEdge(int from, int to, const Capacity &cap) {
		AddEdge(from, to, cap);
		AddEdge(to, from, cap);
	}

	Capacity GetMaxFlow() {
		Capacity flow = 0;
		while (bfs()) {
			flow += dfs(s, inf<Capacity>);
		}
		return flow;
	}

	int GetSource() const {
		return s;
	}

	int GetSink() const {
		return t;
	}

private:
	bool bfs() {
		std::fill(std::begin(lv), std::end(lv), -1);
		std::copy(std::begin(head), std::end(head), std::begin(cur));
		lv[s] = 0;
		std::queue<int> q;
		q.emplace(s);		
		while (!q.empty()) {
			int from = q.front();
			q.pop();
			for (int ed = head[from]; ~ed; ed = edge[ed].next) {
				auto [to, cap, _] = edge[ed];
				if (cap > 0 && lv[to] == -1) {
					lv[to] = lv[from] + 1;
					q.emplace(to);
				}
			}
		}
		return lv[t] != -1;
	}

	Capacity dfs(int from, Capacity flow) {
		if (from == t) {
			return flow;
		}
		auto lesf = flow;
		for (int &ed = cur[from]; ~ed && lesf > 0; ed = edge[ed].next) {
			auto [to, cap, _] = edge[ed];
			if (cap > 0 && lv[to] == lv[from] + 1) {
				auto ret = dfs(to, std::min<Capacity>(cap, flow));
				lesf -= ret;
				edge[ed].cap -= ret;
				edge[ed ^ 1].cap += ret;
			}
		}
		return flow - lesf;
	}

	void AddEdge(int from, int to, const Capacity &cap) {
		edge.emplace_back(to, cap, head[from]); head[from] = int(edge.size()) - 1;
	}
	struct Edge {
		int to;
		Capacity cap;
		int next;
		Edge(int to = {}, Capacity cap = {}, int next = -1) 
			: to{to}, cap{cap}, next{next} {}
	};
	template <typename T> static constexpr T inf = std::numeric_limits<T>::max() / 2;
	std::vector<Edge> edge;
	std::vector<int> head, cur, lv;
	int s, t;
};

using namespace std;

void Main() {
	int n, m;
	cin >> n >> m;

	MaxFlow<int> mf(n * 2 + 2, 0, n * 2 + 1);
	vector<bool> vis(n * 2 + 1);
	for (int i = 0; i < m; i ++) {
		int u, v;
		cin >> u >> v;
		u ++; v ++;
		mf.AddDirectedEdge(u, v + n, 1);
		if (!vis[u]) {
			vis[u] = true;
			mf.AddDirectedEdge(mf.GetSource(), u, 1);
		}
		if (!vis[v + n]) {
			vis[v + n] = true;
			mf.AddDirectedEdge(v + n, mf.GetSink(), 1);
		}
	}
	// cerr << mf.GetMaxFlow() << '\n';
	cout << n - mf.GetMaxFlow() << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}