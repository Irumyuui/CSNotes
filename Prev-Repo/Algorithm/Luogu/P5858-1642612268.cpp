#include <bits/stdc++.h>

using namespace std;

const int LEN = 5e3 + 5;
long long cost[LEN], f[LEN][LEN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, w, s;
    cin >> n >> w >> s;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> cost[i];
    }
    fill(f[0] + 1, f[0] + LEN * LEN, -(1ll << 60));
    deque<int>deq;
    for (int i = 1; i <= n; ++ i)
    {
        deq.clear();
        deq.push_back(w);
        for (int j = w; j > 0; -- j)
        {
            while (!deq.empty() && f[i - 1][j - 1] >= f[i - 1][deq.back()]){
                deq.pop_back();
            }
            deq.push_back(j - 1);
            while (deq.front() > j + s - 1){
                deq.pop_front();
            }
            f[i][j] = f[i - 1][deq.front()] + cost[i] * j;
        }
    }
    long long ans = -(1ll << 60);
    for (int i = 0; i <= w; ++ i)
    {
        ans = max(ans, f[n][i]);
    }
    cout << ans;
    return 0;
}