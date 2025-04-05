#include <iostream>
#include <vector>

typedef long long LL;
const int len = 2;
const LL modp = 1000000007;

using namespace std;

struct Matrix{
    LL arr[len][len];
    Matrix()
    {
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                arr[i][j] = 0;
            }
        }
    }
    void BuildBasic()
    {
        for (int i = 0; i < len; i++)
        {
            arr[i][i] = 1;
        }
    }
};

Matrix operator*(const Matrix &a, const Matrix &b)
{
    Matrix res;
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            for (int k = 0; k < len; k++)
            {
                res.arr[i][j] += (a.arr[i][k] * b.arr[k][j] % modp);
                res.arr[i][j] %= modp;
            }
        }
    }
    return res;
}

Matrix QuickPow(Matrix a, LL i)
{
    Matrix res;
    res.BuildBasic();
    while (i)
    {
        if (i & 1){
            res = res * a;
        }
        a = a * a;
        i >>= 1;
    }
    return res;
}

int main()
{
    Matrix a;
    LL k;
    cin >> k;
    a.arr[0][0] = a.arr[0][1] = a.arr[1][0] = 1;
    Matrix res = QuickPow(a, k - 1);
    cout << res.arr[0][0];
    return 0;
}