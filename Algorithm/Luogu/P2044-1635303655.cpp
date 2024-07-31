#include <iostream>

using namespace std;

typedef long long LL;
const LL N = 2;
LL m, g;

LL slowlyMult(LL a, LL b)
{
    LL res = 0;
    while (b)
    {
        if (b & 1){
            res = (res + a) % m;
        }
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
}

class Matrix
{
public:
    LL arr[N][N];
    Matrix(LL a, LL b)
    {
        this->arr[0][0] = a;
        this->arr[0][1] = 0;
        this->arr[1][0] = b;
        this->arr[1][1] = 0;
    }
    Matrix (LL a, LL b, LL c, LL d)
    {
        this->arr[0][0] = a;
        this->arr[0][1] = b;
        this->arr[1][0] = c;
        this->arr[1][1] = d;
    }
    Matrix operator*(const Matrix &a) const
    {
        Matrix res(0, 0, 0, 0);
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                for (int k = 0; k < N; ++k)
                {
                    res.arr[i][j] = (res.arr[i][j] + slowlyMult(this->arr[i][k], a.arr[k][j])) % m;
                }
            }
        }
        return res;
    }
};

Matrix MatrixPow(Matrix a, LL i)
{
    Matrix res(1, 1);
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
    LL a, c, x0, n;
    cin >> m >> a >> c >> x0 >> n >> g;
    Matrix basic(a, 1, 0, 1);
    Matrix add(x0, 0, c, 0);
    if (n == 0){
        cout << x0 << endl;
        return 0;
    }
    Matrix res = MatrixPow(basic, n);
    res = res * add;
    cout << res.arr[0][0] % g << endl;
    return 0;
}