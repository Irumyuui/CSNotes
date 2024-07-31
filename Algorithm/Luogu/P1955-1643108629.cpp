#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;

const int N = 1e6 + 10;
// int dad[N];
unordered_map<int, int>dad;

struct node
{
    int x, y, k;
    bool operator < (const node &x) const
    {
        return this->k > x.k;
    }
};

int Find(int v)
{
    if (dad[v] != -1)
        return dad[v] = Find(dad[v]);
    return v;
}

bool Union(node x)
{
    int a = Find(x.x);
    int b = Find(x.y);
    if (a == b && x.k == 0){
        return false;
    }else if (a != b && x.k == 1){
        dad[a] = b;  
    }
    return true;
}

void solve()
{
    // fill(all(dad), -1);
    dad.clear();
    int n;
    cin >> n;
    vector<node>v(n);
    for (auto & it : v)
    {
        cin >> it.x >> it.y >> it.k;
        dad[it.x] = -1;
        dad[it.y] = -1;
    }
    sort(all(v));
    for (auto it : v)
    {
        if (!Union(it)){
            cout << "NO" << '\n';
            return;
        }
    }
    cout << "YES" << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int test;
    cin >> test;
    while (test --)
    {
        solve();
    }
    return 0;
}