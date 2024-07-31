#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

template <typename _Capacity>
class DinicMaxFlow {
    private:
        struct _FlowEdge {
            int to;
            _Capacity cap;
            int rev_idx;

            constexpr _FlowEdge(int to = {}, _Capacity cap = {}, int rev_idx = -1)
                : to(to), cap(cap), rev_idx(rev_idx) {}
        };

        using _FlowEdgeList = std::vector<_FlowEdge>;

    public:
        using capacity_type = _Capacity;
        using flow_edge_type = _FlowEdge;    

    private:
        std::vector<_FlowEdgeList> _adj;
        std::vector<int> _cur, _level;
        int _source, _sink;

    public:
        explicit DinicMaxFlow(std::size_t vertex_count, int source, int sink)
            : _adj(vertex_count), _cur(vertex_count), _level(vertex_count), _source(source), _sink(sink) {}

    private:
        auto _AddEdge(int from, int to, _Capacity cap, int rev_idx = -1) -> int {
            int idx = _adj[from].size();
            _adj[from].emplace_back(to, cap, rev_idx);
            return idx;
        }

        auto _Bfs() -> bool {
            std::fill(_level.begin(), _level.end(), -1);
            std::fill(_cur.begin(), _cur.end(), 0);
            
            std::queue<int> q;
            _level[_source] = 0;
            q.emplace(_source);
            while (!q.empty()) {
                int from = q.front();
                q.pop();
                for (int eid = 0; eid < (int)_adj[from].size(); eid += 1) {
                    const auto &[to, cap, _] = _adj[from][eid];
                    if (cap > 0 && _level[to] == -1) {
                        _level[to] = _level[from] + 1;
                        q.emplace(to);
                    }
                }
            }

            return _level[_sink] != -1;
        }

        auto _Dfs(int from, _Capacity total_flow) -> _Capacity {
            if (from == _sink)
                return total_flow;

            auto remain_flow = total_flow;
            for (int &eid = _cur[from]; eid < (int)_adj[from].size(); eid += 1) {
                auto &[to, cap, rev_eid] = _adj[from][eid];
                if (cap > 0 && _level[to] == _level[from] + 1) {
                    auto ret = _Dfs(to, std::min<_Capacity>(remain_flow, cap));
                    remain_flow -= ret;
                    cap -= ret;
                    _adj[to][rev_eid].cap += ret;
                }
            }

            return total_flow - remain_flow;
        }

    public:
        auto Source() const noexcept -> const int& {
            return _source;
        }
        auto Source() noexcept -> int& {
            return _source;
        }
        auto Sink() const noexcept -> const int& {
            return _sink;
        }
        auto Sink() noexcept -> int& {
            return _sink;
        }

        auto AddEdge(int from, int to, _Capacity cap) -> void {
            int eidx = _AddEdge(from, to, cap, _adj[to].size());
            int rev_eidx = _AddEdge(to, from, _Capacity{}, eidx);
        }

        auto AddUEdge(int from, int to, _Capacity cap) -> void {
            int eidx = _AddEdge(from, to, cap, _adj[to].size());
            _AddEdge(to, from, cap, eidx);
        }

        auto GetMaxFlow(_Capacity inf = std::numeric_limits<_Capacity>::max()) -> _Capacity {
            _Capacity flow = {};
            while (_Bfs()) {
                flow += _Dfs(_source, inf);
            }
            return flow;
        }

        auto operator [] (std::size_t index) const -> const _FlowEdgeList& {
            return _adj[index];
        }
        auto operator [] (std::size_t index) -> _FlowEdgeList& {
            return _adj[index];
        }

        auto ClearEdge() -> void {
            for (auto &list : _adj) {
                list.clear();
            }
        }

        auto Size() const -> std::size_t {
            return _adj.size();
        }

        auto Assign(std::size_t vertex_count) -> void {
            _adj.assign(vertex_count, _FlowEdgeList{});
            _cur.resize(vertex_count);
            _level.resize(vertex_count);
        }
};

using i64 = int64_t;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    s -= 1; t -= 1;
    
    DinicMaxFlow<i64> max_flow(n, s, t);
    
    for (int i = 0; i < m; i += 1) {
        int from, to;
        i64 cap;
        std::cin >> from >> to >> cap;
        from -= 1; to -= 1;
        max_flow.AddEdge(from, to, cap);
    }
    
    std::cout << max_flow.GetMaxFlow() << '\n';
}