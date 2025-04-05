#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
const int INF = 0x7FFFFFFF;

int chire, hand;

class apple
{
    public:
        int height;
        int use;
};

bool operator<(const apple &a, const apple &b)
{
    return a.use < b.use;
}

int main()
{
    int n, s;
    cin >> n >> s >> chire >> hand;
    vector<apple>v(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i].height >> v[i].use;
    }
    sort(v.begin(), v.end());
    int res = 0;
    for (auto it : v)
    {
        if (it.height <= chire + hand){
            if (it.use <= s){
                res++;
                s -= it.use;
            }else{
                break;
            }
        }
    }
    cout << res;
    return 0;
}