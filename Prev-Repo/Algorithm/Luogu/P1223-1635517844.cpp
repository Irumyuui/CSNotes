#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
const int INF = 0x7FFFFFFF;

struct Node
{
    int number;
    int water;
};

bool operator<(const Node &a, const Node &b)
{
    if (a.water == b.water){
        return a.number < b.number;
    }
    return a.water < b.water;
}

int main()
{
    int cnt;
    cin >>cnt;
    vector<Node>v(cnt);
    for (int i = 0; i < cnt; ++i)
    {
        v[i].number = i + 1;
        cin >> v[i].water;
    }
    sort(v.begin(), v.end(), less<Node>());
    LD res = 0, sum = 0;
    int space = 0;
    for (int i = 0; i < cnt; ++i)
    {
        if (space == 1){
            cout << ' ';
        }else{
            space = 1;
        }
        cout << v[i].number;
        res += sum;
        sum += v[i].water;
    }
    cout << endl;
    printf("%.2LF", res / cnt);
    return 0;
}