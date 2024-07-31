#include <bits/stdc++.h>
using namespace std;

const int LEN = 1e6 + 10;
array<long long, LEN>arr, cost;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    long long n, k;
    cin >> n;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> arr[i];
        arr[i] += arr[i - 1];
    }
    k = arr[n];
    k /= n;
    for (int i = 1; i < n; ++ i)
    {
        cost[i] = i * k - arr[i];
    }
    sort(cost.begin() + 1, cost.begin() + 1 + n);
    long long ans = 0, ave = cost[n / 2];
    for (int i = 1; i <= n; ++ i)
    {
        ans += llabs(cost[i] - ave);
    }
    cout << ans;
    return 0;
}