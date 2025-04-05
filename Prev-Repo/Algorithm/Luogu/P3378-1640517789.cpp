#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int LEN = 1e6 + 115;
struct MinHeap{
    LL arr[LEN];
    int size;
    MinHeap(){
        fill(arr, arr + LEN, 0);
        size = 0;
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
            if (arr[pos] <= arr[t]){
                return;
            }
            swap(arr[t], arr[pos]);
            pos = t;
        }
    }
    LL &top(){
        return arr[1];
    }
    void push(LL x){
        arr[++ size] = x;
        up(size);
    }
    void pop(){
        arr[1] = arr[size --];
        down(1);
    }
};

MinHeap mh;

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    int c, x;
    while (n --){
        cin >> c;
        if (c == 1){
            cin >> x;
            mh.push(x);
        }else if (c == 2){
            cout << mh.top() << endn;
        }else{
            mh.pop();
        }
    }
    return 0;
}