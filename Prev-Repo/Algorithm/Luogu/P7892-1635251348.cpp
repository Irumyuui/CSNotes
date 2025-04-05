#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int cnt;
    cin >> cnt;
    while (cnt--)
    {
        int n, m;
        cin >> n >> m;
        int can = 0;   
        int a, b;
        for (a = sqrt(n); a >= 1; --a)
        {
            if (n % a == 0){
                b = n / a;
                if ((a + b + 2) * 2 <= m){
                    can = 1;
                }
            }
        }
        if (can){
            cout << "Good" << endl;
        }else{
            cout << "Miss" << endl;
        }
    }
    return 0;
}