#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long LL;
map<LL, LL>m;

int main()
{
    int n, c;
    vector<LL>v;
    cin >> n >> c;
    for (int i = 0; i < n; ++ i)
    {
        LL a;
        cin >> a;
        v.push_back(a);
        m[a] = 0;
    }
    LL res = 0;
    for (auto it : v)
    {
        m[it + c] ++;
    }
    for (auto it : v)
    {
        res += m[it];
    }
    cout << res;
    return 0;
}