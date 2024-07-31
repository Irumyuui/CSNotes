#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10, SIZE = 26;
int child[MAXN][SIZE], tot, fail[MAXN];
int en[MAXN];

void Insert(const string &s) {
    int now = 0;
    for (auto x : s) {
        int cl = x - 'a';
        if (!child[now][cl])
            child[now][cl] = ++ tot;
        now = child[now][cl];
    }
    en[now] = s.size();
}
void build() {
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

int st[MAXN];
int ans[MAXN];
int query(const string &s) {
    int m = 0, now = 0;
    for (int i = 0; i < s.size(); ++ i) {
        now = child[now][s[i] - 'a'];
        m ++;
        st[m] = now; ans[m] = i;
        if (en[now]) {
            m -= en[now];
            now = st[m];
        }
        // cout << s[i] << ' ';
        // for (int j = 1; j <= m; ++ j) {
        //     cout << s[ans[j]];
        // }
        // cout << '\n';
    }
    return m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string t;
    cin >> t;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++ i) {
        string s;
        cin >> s;
        Insert(s);
    }
    build();
    int len = query(t);
    for (int i = 1; i <= len; ++ i) {
        cout << t[ans[i]];
    }
    return 0;
}