#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i ++) {
        int x;
        cin >> x;
        a[x - 1] = i;
    }
    
    vector<int> lc(n, -1), rc(n, -1), stk(n, -1);
    int top = 0;
    for (int i = 0; i < n; i ++) {
        int k = top - 1;
        while (k >= 0 && a[i] < a[stk[k]]) -- k;
        if (k >= 0) rc[stk[k]] = i;
        if (k + 1 < top) lc[i] = stk[k + 1];
        stk[++ k] = i;
        top = k + 1;
    }

    auto dfs = [&](auto &&dfs, int from) {
        if (from == -1) return;
        cout << from + 1 << ' ';
        dfs(dfs, lc[from]);
        dfs(dfs, rc[from]);
    };
    dfs(dfs, stk[0]);
}