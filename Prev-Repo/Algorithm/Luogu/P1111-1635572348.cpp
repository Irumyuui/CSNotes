#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node
{
    public:
        int a, b;
        int time;
};

bool operator<(const Node &a, const Node &b)
{
    return a.time < b.time;
}

vector<int>dad;
int Find(int a)
{
    if (dad[a] != a){
        dad[a] = Find(dad[a]);
    }
    return dad[a];
}

void Union(int a, int b)
{
    a = Find(a);
    b = Find(b);
    dad[a] = b;
}

int main()
{
    int n, m;
    cin >> n >> m;
    dad = vector<int>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        dad[i] = i;
    }
    vector<Node>v(m);
    for (auto &it : v)
    {
        cin >> it.a >> it.b >> it.time;
    }
    sort(v.begin(), v.end(), less<Node>());
    for (auto it : v)
    {
        Union(it.a, it.b);
        int noyet = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (dad[i] == i){
                noyet++;
            }
        }
        if (noyet == 1){
            cout << it.time;
            return 0;
        }
    }
    cout << -1;
    return 0;
}