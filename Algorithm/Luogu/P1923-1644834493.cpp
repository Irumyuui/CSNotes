#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;

int num[int(5e6 + 10)];

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++ i)
    {
        cin >> num[i];
    }
    sort(num, num + n);
    cout << num[k];
    return 0;
}