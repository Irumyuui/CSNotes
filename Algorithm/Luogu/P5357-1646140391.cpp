#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;
const int SIZE = 26;

int child[MAXN][SIZE], fail[MAXN], tot = 0, en[MAXN];
int cnt[MAXN];

void Insert(const string &s, int id) {
    int now = 0;
    for (auto x : s) {
        int cl = x - 'a';
        if (!child[now][cl]) child[now][cl] = ++ tot;
        now = child[now][cl];
    }
    // if (en[now] == 0)
        en[now] = id;
}

void buildfail() {
    queue<int>q;
    for (int i = 0; i < SIZE; ++ i) 
        if (child[0][i])
            q.push(child[0][i]);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < SIZE; ++ i) {
            if (child[now][i]) {
                fail[child[now][i]] = child[fail[now]][i];
                q.push(child[now][i]);
            } else {
                child[now][i] = child[fail[now]][i];
            }
        }
    }
}

void getcnt(const string &s) {
    int now = 0;
    for (const auto x : s) {
        now = child[now][x - 'a'];
        cnt[now] ++;
    }
}

int ind[MAXN], ans[MAXN];
void topsort() {
    for (int i = 1; i <= tot; ++ i)
        ind[fail[i]] ++;
    queue<int>q;
    for (int i = 1; i <= tot; ++ i)
        if (ind[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (!fail[now])
            continue;
        cnt[fail[now]] += cnt[now];
        if (-- ind[fail[now]] == 0)
            q.push(fail[now]);
    }
    for (int i = 1; i <= tot; ++ i) {
        ans[en[i]] = cnt[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    map<string, int>c;
    map<string, int>res;
    vector<string>v(n + 1);
    for (int i = 1; i <= n; ++ i) {
        cin >> v[i];
        c[v[i]] ++;
        res[v[i]] = 0;
        Insert(v[i], i);
    }

    buildfail();
    string t;
    cin >> t;
    getcnt(t);
    topsort();

    for (int i = 1; i <= n; ++ i)
        res[v[i]] = max(res[v[i]], ans[i]);
    for (int i = 1; i <= n; ++ i)
        cout << res[v[i]] << '\n';

    return 0;
}