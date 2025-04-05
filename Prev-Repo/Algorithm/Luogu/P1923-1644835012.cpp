#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    
    vector<int>v(n);

    for (auto &it : v){
        cin >> it;
    }

    sort(v.begin(), v.end());

    cout << v[k] << '\n';

    return 0;
}