#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int main()
{
    int n, q;
    cin >> n >> q;
    vector<map<LL, LL>>v(n + 1, map<LL, LL>());
    while (q--)
    {
        LL a, b, c, d;
        cin >> a >> b >> c;
        if (a == 1){
            cin >> d;
            v[b][c] = d;
        }else{
            cout << v[b][c] << endl;
        }
    }
    return 0;
}