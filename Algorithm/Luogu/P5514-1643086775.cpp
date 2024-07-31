#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    priority_queue<int, vector<int>, greater<int>>q;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++ i)
    {
        int x;
        cin >> x;
        q.push(x);
    }
    while (q.size() > 1)
    {
        int a = q.top();
        q.pop();
        int b = q.top();
        q.pop();
        q.push(a ^ b);
    }
    cout << q.top();
    return 0;
}