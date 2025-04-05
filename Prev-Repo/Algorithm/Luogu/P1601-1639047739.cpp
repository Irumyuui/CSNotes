#include <bits/stdc++.h>

using namespace std;

string Add(const string &n1, const string &n2){
    string s1 = n1, s2 = n2, res;
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    while (s1.size() < s2.size()) s1.push_back('0');
    while (s2.size() < s1.size()) s2.push_back('0');
    int index = 0;
    for (int i = 0; i < s1.size(); ++ i){
        res.push_back(char(((s1[i] - '0') + (s2[i] - '0') + index) % 10 + '0'));
        if ((s1[i] - '0') + (s2[i] - '0') + index >= 10) index = 1;
        else index = 0;
    }
    if (index) res.push_back('1');
    while (res.back() == '0' && res.size() > 1) res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    string n1, n2;
    cin >> n1 >> n2;
    cout << Add(n1, n2) << endl;
    return 0;
}