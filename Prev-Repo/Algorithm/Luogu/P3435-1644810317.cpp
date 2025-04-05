#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int>nex(n);
    string str;

    cin >> str;
    nex[0] = -1;
    for (int i = 1, k = -1; i < n; ++ i){
        while (k > -1 && str[k + 1] != str[i]){
            k = nex[k];
        }
        if (str[k + 1] == str[i]){
            k ++;
        }
        nex[i] = k;
    }

    long long ans = 0;
    for (int i = 0; i < n; ++ i){
        int j = i;
        while (nex[j] > -1){
            j = nex[j];
        }
        if (nex[i] > -1){
            nex[i] = j;
        }
        ans += i - j;
    }

    cout << ans;

    return 0;
}