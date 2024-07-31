#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;
const int INF = 0x7FFFFFFF;

struct Node
{
    int point;
    int milk;
};

bool operator<(const Node &a, const Node &b)
{
    if (a.point == b.point){
        return a.milk > b.milk;
    }
    return a.point < b.point;
}

int main()
{
    int maxmilk, cnt;
    cin >> maxmilk >> cnt;
    vector<Node>v(cnt);
    for (auto &it : v)
    {
        cin >> it.point >> it.milk;
    }
    sort(v.begin(), v.end(), less<Node>());
    int res = 0;
    for (int i = 0; i < cnt && maxmilk > 0; ++i)
    {
        if (v[i].milk <= maxmilk){
            res += (v[i].point * v[i].milk);
            maxmilk -= v[i].milk;
        }else{
            res += (v[i].point * (maxmilk));
            break;
        }
    }
    cout << res << endl;
    return 0;
}