#include <bits/stdc++.h>
using namespace std;

bool check(int len, int k, vector<int> &road){
    int cnt = 0;

    for (int i = 1; i < road.size(); ++ i){
        int rl = road[i] - road[i - 1];
        if (len < rl){
            cnt += rl / len - (rl % len == 0 ? 1 : 0);
        }
    }

    return cnt <= k;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, N, K;
    cin >> L >> N >> K;
    vector<int>road(N);
    for (auto &it : road){
        cin >> it;
    }
    
    int l = 0, r = L, ans = 0;
    while (l <= r){
        int mid = l + ((r - l) >> 1);
        if (check(mid, K, road)){
            ans = mid;
            r = mid - 1;    
        }else{
            l = mid + 1;
        }
    }

    cout << ans;

    return 0;
}