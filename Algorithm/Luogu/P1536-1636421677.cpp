#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

vector<int>dad;

int FIND(int v)
{
    if (dad[v] > 0)
        return dad[v] = FIND(dad[v]);
    return v;
}

void UNION(int a, int b)
{
    a = FIND(a);
    b = FIND(b);
    if (a != b)
        dad[b] = a;
}

int main()
{
    cin.tie(0);
    int n;
    while (cin >> n && n > 0)
    {
        int m;
        cin >> m;
        if (m == 0){
            cout << n - 1 << endl;
            continue;
        }
        dad = vector<int>(n + 1, -1);
        while (m --)
        {
            int a, b;
            cin >> a >> b;
            UNION(a, b);
        }
        int res = 0;
        for (int i = 1; i <= n; ++ i)
        {
            if (dad[i] < 0)
                res ++;
        }
        if (res != 0) cout << res - 1 << endl;
        else cout << 0 << endl;
    }
    return 0;
}