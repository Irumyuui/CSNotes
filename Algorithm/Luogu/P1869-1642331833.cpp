#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t --)
    {
        int n, k;
        cin >> n >> k;
        if ((n & k) == k){
            cout << 1 << '\n';
        }else{
            cout << 0 << '\n';
        }
    }
    return 0;
}