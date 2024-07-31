#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

void solve()
{
    int n, k;
    scanf("%d %d", &n, &k);
    vector<int>v(n + 1);
    for (int i = 1; i <= n; ++ i)
        scanf("%d", &v[i]);
    deque<PII>q;
    int ll = 0, rr = 1;
    while (rr <= k)
    {
        while (!q.empty() && q.back().second < v[rr])
            q.pop_back();
        q.push_back({rr, v[rr]});
        rr ++;
    } 
    printf("%d\n", q.front().second);
    while (ll <= rr && rr < v.size())
    {
        ll ++;
        while (!q.empty() && q.back().second < v[rr])
            q.pop_back();
        q.push_back({rr, v[rr]});
        while (q.front().first <= ll)
            q.pop_front();
        printf("%d\n", q.front().second);
        rr ++;
    }
    return;
}

int main()
{
    solve();    
    return 0;
}