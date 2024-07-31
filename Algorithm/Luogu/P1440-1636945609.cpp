#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

deque<int>minans;
// vector<int>ans;

void getmin(const vector<int> &v, const int &k)
{
    int ll = 0, rr = 1;
    while (rr <= k)
    {
        if (minans.empty())
            // ans.push_back(0);
            printf("0\n");
        else
            // ans.push_back(v[minans.front()]);
            printf("%d\n", v[minans.front()]);
        while (minans.size() && v[minans.back()] > v[rr])
            minans.pop_back();
        minans.push_back(rr);
        rr ++;
    }
    while (ll <= rr && rr < v.size())
    {
        ll ++;
        
        if (minans.empty())
            // ans.push_back(0);
            printf("0\n");
        else
            // ans.push_back(v[minans.front()]);
            printf("%d\n", v[minans.front()]);
        while (minans.size() && v[minans.back()] > v[rr])
            minans.pop_back();
        while (minans.size() && minans.front() <= ll)
            minans.pop_front();
        minans.push_back(rr);
        rr ++;
    }
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>v(n + 1);
    for (int it = 1; it <= n; ++ it)
    {
        scanf("%d", &v[it]);
    }
    getmin(v, k);
}

int main()
{
    // cin.tie(0);
    // FAST();
    solve();
    return 0;
}