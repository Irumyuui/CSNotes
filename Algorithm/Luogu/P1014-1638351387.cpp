#include <bits/stdc++.h>
#define FAST() std::ios::sync_with_stdio(false)
inline void FREIN(const char *text){freopen(text, "r", stdin);}
using namespace std;

void solve(){
    int n, i = 0;
    cin >> n;
    for (i = 0; n > i; ++ i)
        n -= i;
    int a = i + 1, b = 0;
    while (n --){
        a --;
        b ++;
    }
    if (i & 1){
        cout << a << '/' << b << endl;
    }else{
        cout << b << '/' << a << endl;
    }
}

int main(){
    FAST(); 
    //FREIN("in.in");
    solve();
    return 0;
}