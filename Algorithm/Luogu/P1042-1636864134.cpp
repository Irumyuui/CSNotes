#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

int main()
{
    cin.tie(0);
    string s;
    char x;
    while (cin >> x && x != 'E')
    {
        s.push_back(x);
    }
    int a, b;
    a = b = 0;
    for (auto it : s)
    {
        if (it == 'W'){
            a ++;
        }else{
            b ++;
        }
        if ((a >= 11 || b >= 11) && (abs(a - b) >= 2)){
            cout << a << ':' << b << endl;
            a = b = 0;
        }
    }
    // if (a || b){
        cout << a << ':' << b << endl;
        a = b = 0;
    // }
    cout << endl;
    for (auto it : s)
    {
        if (it == 'W'){
            a ++;
        }else{
            b ++;
        }
        if ((a >= 21 || b >= 21) && abs(a - b) >= 2){
            cout << a << ':' << b << endl;
            a = b = 0;
        }
    }
    // if (a || b){
        cout << a << ':' << b << endl;
    // }
    return 0;
}