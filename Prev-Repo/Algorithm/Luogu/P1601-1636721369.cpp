#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string HeighAdd(const string &num1, const string &num2)
{
    string bignum = num1;
    string smanum = num2;
    if (bignum.size() < smanum.size()){
        bignum.swap(smanum);
    }
    while (smanum.size() < bignum.size())
    {
        smanum.push_back('0');
    }
    int up = 0;
    string res;
    for (int i = 0; i < bignum.size(); ++ i)
    {
        int a = bignum[i] - '0', b = smanum[i] - '0';
        res.push_back((a + b + up) % 10 + '0');
        up = (a + b + up) / 10;
    }
    if (up){
        res.push_back('1');
    }
    return res;
}

int main()
{
    string num1, num2;
    cin >> num1 >> num2;
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    string res = HeighAdd(num1, num2);
    reverse(res.begin(), res.end());
    cout << res;
    return 0;
}