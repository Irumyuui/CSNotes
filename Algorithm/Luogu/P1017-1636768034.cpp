#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

string solve(int num, int k)
{
    string ans;
    do
    {
        int m = num % k;
        int x = num / k;
        if (m < 0){
            m += abs(k);
            x ++;
        }
        num = x;
        if (m < 10) ans.push_back((char)(m + '0'));
        else ans.push_back((char)(m - 10 + 'A'));
    } while (num != 0);
    reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    int num, k;
    cin >> num >> k;
    string ans = solve(num, k);
    cout << num << "=" << ans << "(base" << k << ")" << endl;
    return 0;
}