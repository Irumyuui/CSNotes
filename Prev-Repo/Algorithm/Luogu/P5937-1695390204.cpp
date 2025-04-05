#include <bits/stdc++.h>

template <typename Vector>
#ifdef __cpp_concepts
    requires requires(Vector a, Vector b) {
        { a + b } -> std::same_as<Vector>;
        { -a } -> std::same_as<Vector>;
        { a += b };
    }
#endif
class WeidgeDisjointSet {
private:
    std::vector<int> _leader;
    std::vector<Vector> _vector;

public:
    using vector_type = Vector;
    using value_type = Vector;

private:
    static void _IotaInitLeader(std::vector<int> &leader) {
        std::iota(leader.begin(), leader.end(), 0);
    }

public:
    explicit WeidgeDisjointSet(std::size_t size, Vector vec)
        : _leader(size), _vector(size, vec) {
        _IotaInitLeader(_leader);
    }

    int GetLeader(int x) {
        if (_leader[x] == x) {
            return x;
        }
        int fa = _leader[x];
        _leader[x] = GetLeader(_leader[x]);
        _vector[x] += _vector[fa];
        return _leader[x];
    }

    bool MergeTo(int from, int to, Vector vec) {
        int ra = GetLeader(from), rb = GetLeader(to);
        if (ra == rb) {
            return false;
        }
        _vector[ra] = -_vector[from] + vec + _vector[to];
        _leader[ra] = rb;
        return true;
    }

    bool IsSame(int a, int b) noexcept {
        return GetLeader(a) == GetLeader(b);
    }

    Vector Ask(int from, int to) const {
        return _vector[from] + -_vector[to];
    }

    void Assign(std::size_t size, Vector vec) {
        _leader.resize(size);
        _IotaInitLeader(_leader);
        _vector.assign(size, vec);
    }
};

struct Vector {
    int cnt = 0;
    constexpr Vector(int cnt = 0) : cnt(cnt) {}
    friend constexpr Vector operator + (const Vector &a, const Vector &b) {
        return Vector{a.cnt ^ b.cnt};
    }
    constexpr Vector &operator += (const Vector &o) {
        *this = *this + o;
        return *this;
    }
    constexpr Vector operator - () const {
        return *this;
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    // [l, r] => [1, r] - [1, l - 1]
    struct Query {
        int l, r, cnt;
    };
    std::vector<Query> que(q);
    std::vector<int> list{{}};
    list.reserve(q * 2);
    for (auto &[l, r, cnt] : que) {
        std::string s;
        std::cin >> l >> r >> s;
        if (s == "odd") {
            cnt = 1;
        } else {
            cnt = 0;
        }
        l --;
        list.emplace_back(l);
        list.emplace_back(r);
    }

    std::ranges::sort(list);
    list.erase(std::ranges::unique(list).begin(), list.end());
    WeidgeDisjointSet<Vector> dsu(list.size(), 0);
    int ans = 0;
    for (auto [l, r, cnt] : que) {
        l = std::ranges::lower_bound(list, l) - list.begin();
        r = std::ranges::lower_bound(list, r) - list.begin();
        
        if (dsu.IsSame(l, r)) {
            auto ret = dsu.Ask(l, r);
            if (ret.cnt != cnt) {
                break;
            }    
        } else {
            dsu.MergeTo(r, l, cnt);
        }
        ans ++;
    }

    std::cout << ans << '\n';
}