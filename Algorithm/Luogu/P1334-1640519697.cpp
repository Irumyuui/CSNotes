#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int LEN = 2e4 + 115;
struct minheap{
    LL arr[LEN];
    int size;
    minheap(){
        size = 0;
        fill(arr, arr + LEN, 0);
    }
    void up(int pos){
        while (pos > 1 && arr[pos] < arr[pos >> 1]){
            swap(arr[pos], arr[pos >> 1]);
            pos >>= 1;
        }
    }
    void down(int pos){
        while ((pos << 1) <= size){
            int t = pos << 1;
            if (t + 1 <= size && arr[t] > arr[t + 1]){
                t ++;
            }
            if (arr[t] >= arr[pos]){
                return;
            }
            swap(arr[t], arr[pos]);
            pos = t;
        }
    }
    void push(LL x){
        arr[++ size] = x;
        up(size);
    }
    LL top(){
        LL res = arr[1];
        arr[1] = arr[size --];
        down(1);
        return res;
    }
}h;

LL n, len, ans;

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin >> n;
    h.size = n;
    for (int i = 1; i <= n; ++ i){
        cin >> h.arr[i];
        // le
    }
    for (int i = 1; i <= n; ++ i){
        h.up(i);
    }
    while (h.size > 1){
        LL a = h.top(), b = h.top();
        ans += a + b;
        h.push(a + b);
    }
    cout << ans << endn;
    return 0;
}