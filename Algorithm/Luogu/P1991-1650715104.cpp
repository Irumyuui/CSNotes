#include <bits/stdc++.h>
using namespace std;

#define all(x) std::begin(x), std::end(x)
#define rep(x, a, b) for (int x = (a); x < (b); ++ x)
#define per(x, b, a) for (int x = (b - 1); x >= a; -- x)
#define SZ(x)  static_cast<int>((x).size())
#define pb push_back
#define pf push_front
#define FOR(x, v) for (auto &x : (v))
#define FORC(x, v) for (const auto &x : (v))

#define vec std::vector
using ll = long long;
using ull = unsigned long long;
using ill = __int128_t;
using db = double;
using ld = long double;

struct node {
    int i, j;
    db l;
};

const int MAXN = 1e5 + 10;
int dad[MAXN];
int Find(int v) {
    if (dad[v] != v) {
        return dad[v] = Find(dad[v]);
    }
    return v;
}
bool Union(int a, int b) {
    a = Find(a); b = Find(b);
    if (a == b)
        return false;
    dad[a] = b;
    return true;
}

signed main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int s, n;
    cin >> s >> n;
    vector< pair<db, db> > p(n);
    for (auto &[x, y] : p) {
        cin >> x >> y;
    }
    vector<node> e;
    for (int i = 0; i < n - 1; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            auto &[a, b] = p[i]; auto &[c, d] = p[j];
            db len = sqrt((a - c) * (a - c) + (b - d) * (b - d));
            e.pb(node{i, j, len});
        }
    }
    sort(all(e), [](auto &a, auto &b) {
        return a.l < b.l;
    });

    iota(all(dad), 0);
    int cnt = 0;
    for (auto &[i, j, l] : e) {
        if (Union(i, j)) {
            cnt ++;
        }
        if (cnt + s == n) {
            cout << fixed << setprecision(2) << l;
            break;
        }
    }


    return 0;
}