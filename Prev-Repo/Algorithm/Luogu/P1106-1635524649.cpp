#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
const int INF = 0x7FFFFFFF;

int w[200];
string num1, num2;

int main()
{
    cin >> num1;
    int k;
    cin >> k;
    // num2 = num1;
    // sort(num2.begin(), num2.end());
    while (k--)
    {
        char before = num1[0];
        int del = 0;
        for (int i = 1; i < num1.size(); ++i)
        {
            if (before > num1[i]){
                num1.erase(i - 1, 1);
                del = 1;
                break;
            }else{
                before = num1[i];
            }
        }
        if (del == 0){
            num1.pop_back();
        }
    }
    int front0 = 0;
    for (auto it : num1)
    {
        if (it != '0'){
            front0 = 1;
        }
        if (front0 == 1){
            cout << it;
        }
    }
    if (front0 == 0){
        cout << "0";
    }
    return 0;
}