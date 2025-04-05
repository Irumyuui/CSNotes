#include <bits/stdc++.h>
using namespace std;

struct Trie{
    Trie *child[2];
    Trie(){
        child[0] = child[1] = nullptr;
    }
    #define lc child[1]
    #define rc child[2]
    #define ch child
};

struct edge{
    int v, w;
    edge(const int &v_, const int &w_) : v(v_), w(w_){};
};

vector<edge>g[100010];

inline void addedge(int u, int v, int w){
    g[u].push_back(edge(v, w));
}

int dist[100010];
bool vis[100010];

void dfs(int u){
    vis[u] = true;
    for (const auto &ed : g[u]){
        if (!vis[ed.v]){
            dist[ed.v] = dist[u] ^ ed.w;
            dfs(ed.v);
        }
    }
}

Trie *root_ = nullptr;

void Insert(Trie *&root, int x){
    if (root == nullptr){
        root = new Trie();
    }
    Trie *node = root;
    for (int i = 30; i >= 0; -- i){
        int bit = (x & (1 << i)) > 0;
        if (node->ch[bit] == nullptr){
            node->ch[bit] = new Trie();
        }
        node = node->ch[bit];
    }
}

int solve(Trie *root, int x){
    int res = 0;
    for (int i = 30; i >= 0; -- i){
        int bit = (x & (1 << i)) > 0;
        if (root->ch[!bit] != nullptr){
            res += 1 << i;
            root = root->child[!bit];
        }else{
            root = root->ch[bit];
        }
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i < n; ++ i){
        int u, v, w;
        cin >> u >> v >> w;
        addedge(u, v, w);
        addedge(v, u, w);
    }
    
    dist[1] = 0;
    dfs(1);
    int ans = 0;

    for (int i = 1; i <= n; ++ i){
        int &addn = dist[i];
        Insert(root_, addn);
        ans = max(ans, solve(root_, addn));
    }

    cout << ans << '\n';

    return 0;
}