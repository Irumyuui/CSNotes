#include <iostream>
#include <vector>

#define MOD(X) (X % 10000)

using namespace std;

int main()
{
    int a;
    char ch;
    vector<int>v;
    scanf("%d", &a);
    v.push_back(MOD(a));
    while (scanf("%c", &ch) != EOF && scanf("%d", &a) != EOF)
    {
        if (ch == '*'){
            v.back() = MOD(v.back() * MOD(a));
        }else{
            v.push_back(MOD(a));
        }
    }
    int sum = 0;
    for (auto it : v)
    {
        sum += it;
    }
    cout << MOD(sum) << endl;
    return 0;
}