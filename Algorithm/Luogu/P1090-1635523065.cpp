#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
const int INF = 0x7FFFFFFF;

int main()
{
    priority_queue<int, vector<int>, greater<int>>q;
    int n;
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        q.push(x);
    }
    int res = 0;
    if (q.size() == 1){
        res = q.top();
    }
    while (q.size() != 1)
    {
        int a = q.top();
        q.pop();
        int b = q.top();
        q.pop();
        q.push(a + b);
        res += (a + b);
    }
    cout << res;
    return 0;
}