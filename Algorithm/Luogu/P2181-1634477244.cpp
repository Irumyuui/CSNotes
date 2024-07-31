#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    if (n <= 3){
        cout << 0;
    }else{
        long double res = 1;
        for (int i = 0; i < 4; ++i)
        {
            res *= n;
            n--;
        }
        printf("%.0LF", res / 24);
    }
    return 0;
}