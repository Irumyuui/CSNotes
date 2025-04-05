#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

bool isPrime(const int &a)
{
    if (a < 2){
        return false;
    }else if (a == 2){
        return true;
    }else if (a % 2 == 0){
        return false;
    }else{
        for (int i = 3; i < a; i += 2)
        {
            if (a % i == 0){
                return false;
            }
        }
        return true;
    }
}

int k, _cnt = 0;
vector<int>num;
void f(int v, int cnt, int sum)
{
    for (int i = v + 1; i < num.size() && cnt != k; ++i)
    {
        f(i, cnt + 1, sum + num[i]);
    }
    if (isPrime(sum) && cnt == k){
        _cnt++;
    }
}

int main()
{
    int n;
    cin >> n >> k;
    while (n--)
    {
        int x;
        cin >> x;
        num.push_back(x);
    }
    f(-1, 0, 0);
    cout << _cnt;
    return 0;
}