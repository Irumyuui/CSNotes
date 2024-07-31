#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int>nex;

void KMP(const string &text, const string &patten)
{
    nex = vector<int>(patten.size(), 0);
    int k = nex[0] = -1;
    for (int i = 1; i < patten.size(); ++ i)
    {
        while (k > -1 && patten[k + 1] != patten[i])
        {
            k = nex[k];
        }
        if (patten[k + 1] == patten[i]){
            k ++;
        }
        nex[i] = k;
    }
    k = -1;
    for (int i = 0; i < text.size(); ++ i)
    {
        while (k > -1 && patten[k + 1] != text[i])
        {
            k = nex[k];
        }
        if (patten[k + 1] == text[i]){
            k ++;
        }
        if (k == patten.size() - 1){
            cout << (i - patten.size() + 1 + 1) << endl;
            k = nex[k];
        }
    }
}

int main()
{
    string text, patten;
    cin >> text >> patten;
    KMP(text, patten);
    for (auto it : nex)
        cout << it + 1 << ' ';
    return 0;
}
