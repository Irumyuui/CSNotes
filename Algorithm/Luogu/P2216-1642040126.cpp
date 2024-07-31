#include <bits/stdc++.h>
#define endn '\n'
using namespace std;

typedef long long LL;

const int LEN = 1010;
int arr[LEN][LEN], max1[LEN][LEN], max2[LEN][LEN], min1[LEN][LEN], min2[LEN][LEN];
deque<int>maxq, minq;
int a, b, n;

void solve()
{
    cin >> a >> b >> n;
    for (int i = 1; i <= a; ++ i)
    {
        for (int j = 1; j <= b; ++ j)
        {
            cin >> arr[i][j];
        }
    }
    for (int i = 1; i <= a; ++ i)
    {
        maxq.clear();
        minq.clear();
        for (int j = 1; j < n; ++ j)
        {
            while (!maxq.empty() && arr[i][maxq.back()] <= arr[i][j])
            {
                maxq.pop_back();
            }
            maxq.push_back(j);

            while (!minq.empty() && arr[i][minq.back()] >= arr[i][j])
            {
                minq.pop_back();
            }
            minq.push_back(j);
        }
        // max1[i][1] = arr[i][maxq.front()];
        for (int j = n; j <= b; ++ j)
        {
            while (!maxq.empty() && arr[i][maxq.back()] <= arr[i][j])
            {
                maxq.pop_back();
            }
            maxq.push_back(j);
            while (maxq.front() + n - 1 < j)
            {
                maxq.pop_front();
            }
            max1[i][j - n + 1] = arr[i][maxq.front()];

            while (!minq.empty() && arr[i][minq.back()] >= arr[i][j])
            {
                minq.pop_back();
            }
            minq.push_back(j);
            while (minq.front() + n - 1 < j)
            {
                minq.pop_front();
            }
            min1[i][j - n + 1] = arr[i][minq.front()];
        }
    }
    for (int i = 1; i <= b - n + 1; ++ i)
    {
        maxq.clear();
        minq.clear();
        for (int j = 1; j < n; ++ j)
        {
            while (!maxq.empty() && max1[maxq.back()][i] <= max1[j][i])
            {
                maxq.pop_back();
            }
            maxq.push_back(j);

            while (!minq.empty() && min1[minq.back()][i] >= min1[j][i])
            {
                minq.pop_back();
            }
            minq.push_back(j);
        }
        for (int j = n; j <= a; ++ j)
        {
            while (!maxq.empty() && max1[maxq.back()][i] <= max1[j][i])
            {
                maxq.pop_back();
            }
            maxq.push_back(j);
            while (maxq.front() + n - 1 < j)
            {
                maxq.pop_front();
            }
            max2[j - n + 1][i] = max1[maxq.front()][i];

            while (!minq.empty() && min1[minq.back()][i] >= min1[j][i])
            {
                minq.pop_back();
            }
            minq.push_back(j);
            while (minq.front() + n - 1 < j)
            {
                minq.pop_front();
            }
            min2[j - n + 1][i] = min1[minq.front()][i];
        }
    }
    int ans = 0x7fffffff;
    for (int i = 1; i <= a - n + 1; ++ i)
    {
        for (int j = 1; j <= b - n + 1; ++ j)
        {
            ans = min(ans, abs(max2[i][j] - min2[i][j]));
        }
    }
    cout << ans << endn;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}