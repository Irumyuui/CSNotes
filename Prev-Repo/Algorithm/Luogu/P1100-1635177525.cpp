#include <iostream>

using namespace std;

int main()
{
    unsigned int number, a, b, res = 0;
    cin >> number;
    a = number >> 16;
    b = number << 16;
    res = a + b;
    cout << res;
    return 0;
}