#include <bits/stdc++.h>
using namespace std;

struct edge{
    int a, b, w;
    edge() = default;
    edge(int a, int b, int w){
        this->a = a;
        this->b = b;
        this->w = w;
    }
    bool operator<(const edge &a) const{
        return this->w < a.w;
    }
    bool operator>(const edge &a) const{
        return this->w > a.w;
    }
};

int n, m;
vector<edge>v;
vector<int>dad;

int FindDad(int v){
    if (dad[v] != -1){
        return dad[v] = FindDad(dad[v]);
    }
    return v;
}

bool Union(int a, int b){
    a = FindDad(a);
    b = FindDad(b);
    if (a == b){
        return false;
    }
    dad[a] = b;
    return true;
}

void solve(){
    vector<edge>tree;
    for (auto it : v){
        if (tree.size() == n - 1){
            break;
        }
        if (Union(it.a, it.b)){
            tree.push_back(it);
        }
    }
    if (tree.size() != n - 1){
        cout << "orz" << endl;
        return;
    }
    int ans = 0;
    for (auto it : tree){
        ans += it.w;
    }
    cout << ans << endl;
}

int main(){
    std::ios::sync_with_stdio(false);
    //freopen("in.in", "r", stdin);
    cin >> n >> m;
    dad = vector<int>(n + 1, -1);
    for (int i = 0; i < m; ++ i){
        int a, b, w;
        cin >> a >> b >> w;
        v.push_back(edge(a, b, w));
        // v.push_back(edge(b, a, w));
    }
    sort(v.begin(), v.end(), less<edge>());
    solve();
    return 0;
}