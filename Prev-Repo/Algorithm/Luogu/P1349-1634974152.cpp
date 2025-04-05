#include <iostream>

using namespace std;
typedef long long LL;
const int len = 2;
LL m;

class Matrix
{
    public:
        LL arr[len][len];
        void Fill(LL x)
        {
            for (int i = 0; i < len; ++i)
            {
                for (int j = 0; j < len; ++j)
                {
                    this->arr[i][j] = x;
                }
            }
        }
        void BuildBasic()
        {
            this->Fill(0);
            for (int i = 0; i < len; ++i)
            {
                this->arr[i][i] = 1;
            }
        }
};

Matrix operator*(const Matrix &a, const Matrix &b)
{
    Matrix res;
    res.Fill(0);
    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < len; ++j)
        {
            for (int k = 0; k < len; ++k)
            {
                res.arr[i][j] = (res.arr[i][j] + a.arr[i][k] * b.arr[k][j] % m) % m;
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
    LL p, q, a1, a2, k;
    cin >> p >> q >> a1 >> a2 >> k >> m;
    Matrix a;
    a.arr[0][0] = p;
    a.arr[0][1] = q;
    a.arr[1][0] = 1;
    a.arr[1][1] = 0;
    if (k == 1){
        cout << a1;
    }else if (k == 2){
        cout << a2;
    }else{
        Matrix res = QuickPow(a, k - 2);
        cout << (res.arr[0][0] * a2 + res.arr[0][1] * a1) % m;
    }
    return 0;
}