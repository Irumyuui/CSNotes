#include <bits/stdc++.h>
using namespace std;

#define all(X) std::begin(X), std::end(X)
#define cauto const auto
#define endn '\n'

using ll = long long;
using LL = __int128_t;

const int MAXN = 1e6 + 10;
const int SIZE = 26;

int cnt[MAXN];
struct ACAM {
    int child[MAXN][SIZE];
    int tot;
    int end[MAXN];
    int fail[MAXN];
    inline void clear() {
        memset(child, 0, sizeof(child));
        memset(end, 0, sizeof(end));
        memset(fail, 0, sizeof(fail));
        tot = 0;
    }
    void insert(const string &s, int id) {
        int now = 0;
        for (auto x : s) {
            int cl = x - 'a';
            if (!child[now][cl]) {
                child[now][cl] = ++ tot;
            }
            now = child[now][cl];
        }
        end[now] = id;
    }
    void build() {
        queue<int>q;
        for (int i = 0; i < SIZE; ++ i) {
            if (child[0][i]) {
                q.push(child[0][i]);
            }
        }
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            // cout << "here" << '\n';
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
        for (auto x : s) {
            now = child[now][x - 'a'];
            for (int i = now; i; i = fail[i]) {
                if (end[i]) {
                    cnt[end[i]] ++;
                }
            }
        }
    }
}acam;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    int n;
    while (cin >> n && n) {
        acam.clear();
        memset(cnt, 0, sizeof(cnt));

        vector<string>v(n + 1);
        for (int i = 1; i <= n; ++ i) {
            cin >> v[i];
            acam.insert(v[i], i);      
        }

        acam.build();

        string t;
        cin >> t;
        acam.getcnt(t);

        int mx = 0;
        for (int i = 1; i <= n; ++ i) {
            mx = max(mx, cnt[i]);
        }
        cout << mx << '\n';
        for (int i = 1; i <= n; ++ i) {
            if (mx == cnt[i])
                cout << v[i] << '\n';
        }
    }

    return 0;
}