#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
const int INF = 0x7FFFFFFF;

class times
{
    public:
        int at, ot;
};

bool operator<(const times &a, const times &b)
{
    return a.ot < b.ot;
}

int main()
{
    int n;
    cin >> n;
    vector<times>v(n);
    for (auto &it : v)
    {
        cin >> it.at >> it.ot;
    }
    sort(v.begin(), v.end());
    int lastt = 0, res = 0;
    for (auto it : v)
    {
        if (it.at >= lastt){
            lastt = it.ot;
            res++;
        }
    }
    cout << res;
    return 0;
}