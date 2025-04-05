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
    int n, m;
    cin >> n >> m;
    vector<int>v(n);
    vector<int>panter(m + 1, 0);
    for (auto &it : v)
    {
        cin >> it;
    }
    int ll = 0, rr = 0, cnt = 0;
    int res = INFI, resL, resR;
    while (1)
    {
        while (cnt < m && rr < n)
        {
            if (++ panter[v[rr]] == 1)
                cnt ++;
            rr ++;
        }
        if (cnt < m)
            break;
        if (rr - ll < res){
            res = rr - ll;
            resL = ll + 1;
            resR = rr;
        }
        if (-- panter[v[ll]] == 0)
            cnt --;
        ll ++;
    }
    cout << resL << " " << resR << endl;
}

int main()
{
    FAST();
    solve();   
    return 0;
}