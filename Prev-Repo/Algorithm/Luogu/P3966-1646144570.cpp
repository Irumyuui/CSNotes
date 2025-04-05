#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10, SIZE = 26;
int child[MAXN][SIZE], tot = 0, en[MAXN], fail[MAXN], cnt[MAXN];
void Insert(const string &s, int id) {
    int now = 0;
    for (auto x : s) {
        int cl = x - 'a';
        if (child[now][cl] == 0)
            child[now][cl] = ++ tot;
        now = child[now][cl];
        cnt[now] ++;
    }
    if (!en[now])
        en[now] = id;
}
void build() {
    queue<int>q;
    for (int i = 0; i < SIZE; ++ i) if (child[0][i]) q.push(child[0][i]);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < SIZE; ++ i) {
            if (child[now][i])
                fail[child[now][i]] = child[fail[now]][i], q.push(child[now][i]);
            else
                child[now][i] = child[fail[now]][i];
        }
    }
}
int ind[MAXN], ans[MAXN];
void tops() {
    for (int i = 1; i <= tot; ++ i) if (fail[i]) ind[fail[i]] ++;
    queue<int>q;
    for (int i = 1; i <= tot; ++ i) if (ind[i] == 0) q.push(i);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        // cout << now << ' ' << cnt[now] << '\n';
        if (fail[now] == 0) continue;
        cnt[fail[now]] += cnt[now];
        if (-- ind[fail[now]] == 0) q.push(fail[now]);
    }
    for (int i = 1; i <= tot; ++ i)
        if (en[i]) ans[en[i]] = cnt[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string>v(n + 1);
    map<string, int>res;
    for (int i = 1; i <= n; ++ i) {
        cin >> v[i];
        Insert(v[i], i);
        res[v[i]] = 1;
    }
    build();
    tops();
    for (int i = 1; i <= n; ++ i) {
        res[v[i]] = max(res[v[i]], ans[i]);
    }
    for (int i = 1; i <= n; ++ i) cout << res[v[i]] << '\n';

    return 0;
}