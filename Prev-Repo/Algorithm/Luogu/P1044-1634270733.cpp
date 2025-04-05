#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int *arr = new int[n + 1];
    arr[0] = arr[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        int sum = 0;
        for (int k = 0; k < (i >> 1); ++k)
        {
            sum += arr[k] * arr[i - k - 1];
        }
        sum <<= 1;
        if (i & 1){
            sum += arr[i >> 1] * arr[i - (i >> 1) - 1];
        }
        arr[i] = sum;
    }
    cout << arr[n] << endl;
    return 0;
}