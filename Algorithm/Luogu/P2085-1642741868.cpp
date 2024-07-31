#include <bits/stdc++.h>
using namespace std;

struct func
{
    int a, b, c, x, res;
};

bool operator > (const func &a, const func &b)
{
    return a.res > b.res;
}

priority_queue<func, vector<func>, greater<func>>q;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    while (n --)
    {
        func x;
        cin >> x.a >> x.b >> x.c;
        x.x = 1;
        x.res = x.a * x.x * x.x + x.b * x.x + x.c;
        q.push(x);
    }
    for (int i = 1; i <= m; ++ i)
    {
        func x = q.top();
        q.pop();
        cout << x.res << ' ';
        x.x ++;
        x.res = x.a * x.x * x.x + x.b * x.x + x.c;
        q.push(x);
    }
    return 0;
}