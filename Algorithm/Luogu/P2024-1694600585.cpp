#include <bits/stdc++.h>

template <typename Vector>
class DisjionSetUnion {
private:
    std::vector<int> leader;
    std::vector<Vector> vec;

public:
    explicit DisjionSetUnion(std::size_t n, Vector initVec)
        : leader(n), vec(n, initVec) {
        std::iota(leader.begin(), leader.end(), 0);
    }

    int GetLeader(int x) {
        if (leader[x] == x) {
            return x;
        }
        int f = leader[x];
        leader[x] = GetLeader(leader[x]);
        vec[x] += vec[f];
        return leader[x];
    }

    void MergeTo(int a, int b, Vector v) {
        int ra = GetLeader(a);
        int rb = GetLeader(b);
        if (ra == rb) {
            return;
        }
        vec[ra] = -vec[a] + v + vec[b];
        leader[ra] = rb;
    }

    bool IsSame(int a, int b) {
        return GetLeader(a) == GetLeader(b);
    }

    Vector Ask(int a, int b) {
        return vec[a] + -vec[b];
    }
};

struct Vector {
    int info;

    Vector(int info) : info(info) {
        
    }

    friend Vector operator + (const Vector &a, const Vector &b) {
        auto ret = a.info + b.info;
        if (ret == 2) {
            ret = -1;
        } else if (ret == -2) {
            ret = 1;
        }
        return {ret};
    }
    Vector& operator += (const Vector &a) {
        *this = *this + a;
        return *this;
    }

    Vector operator - () const {
        return {-info};
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    DisjionSetUnion<Vector> dsu(n, 0);
    int cnt = 0;
    for (int i = 0; i < q; i ++) {
        int opt, u, v;
        std::cin >> opt >> u >> v;
        u --; v --;
        
        if (u >= n || v >= n || (opt == 2 && u == v)) {
            cnt ++;
            continue;
        } else if (opt == 1 && u == v) {
            continue;
        }

        if (opt == 1) {
            if (dsu.IsSame(u, v)) {
                if (dsu.Ask(u, v).info != 0) {
                    cnt ++;
                }
            } else {
                dsu.MergeTo(u, v, 0);
            }
        } else {
            if (dsu.IsSame(u, v)) {
                if (dsu.Ask(u, v).info != 1) {
                    cnt ++;
                }
            } else {
                dsu.MergeTo(u, v, 1);
            }
        }
    }

    std::cout << cnt << '\n';
}