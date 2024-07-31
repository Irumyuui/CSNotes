#include <bits/stdc++.h>

using namespace std;

const int LEN = 1919;
bool f[LEN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int arr[] = {1, 2, 3, 5, 10, 20};
    f[0] = 1;
    for (auto w : arr)
    {
        int x;
        cin >> x;
        for (int j = x; j > 0; -- j)
        {
            for (int k = 1000; k >= 0; -- k)
            {
                if (f[k]){
                    f[k + w] = 1;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= 1000; ++ i)
    {
        if (f[i]) ans ++;
    }
    cout << "Total=" << ans;
    return 0;
}