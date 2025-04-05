#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    string s;
    cin >> s;
    vector<int>a(s.size(), 0), b(s.size(), 0);
    bool zz = 1;
    for (int i = s.size() - 1; i >= 0; -- i)
    {
        if (s[i] == 'Z' && zz){
            continue;
        }else if (s[i] == 'Z' && zz == false){
            cout << -1;
            return 0;
        }else if (s[i] == 'X'){
            zz = 0;
            a[i] = 1;
        }else{
            zz = 0;
            b[i] = 1;
        }
    }
    for (auto it : a) cout << it;
    cout << '\n';
    for (auto it : b) cout << it;
    cout << '\n';
    return 0;
}