#include <iostream>

using namespace std;

int main()
{
    int hash[10];
    for (int i = 192; i < 400; ++i)
    {
        for (auto &it : hash)
        {
            it = 0;
        }
        int num[3];
        for (int j = 0; j < 3; ++j)
        {
            num[j] = i * (j + 1);
            int x = num[j];
            do{
                hash[x % 10] = 1;
                x /= 10;
            }while (x != 0);
        }
        int res = 0;
        for (int j = 1; j <= 9; ++j)
        {
            res += hash[j];
        }
        if (res == 9){
            cout << num[0] << ' ' << num[1] << ' ' << num[2] << endl;
        }
    }
    return 0;
}