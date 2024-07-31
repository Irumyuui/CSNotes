#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

unordered_map<string, int>ump;

void solve()
{
    int n;
    cin >> n;
    getchar();
    string str;
    int res = 0;
    while (n --)
    {
        cin >> str;
        if (ump.find(str) == ump.end()){
            res ++;
            ump[str] ++;
        }
    }
    cout << res;
    return;
}

int main()
{
    solve();
    return 0;
}