#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int>v1, v2, s;
    while (n--)
    {
        v1.clear();
        v2.clear();
        s.clear();
        int cnt;
        cin >> cnt;
        int x, i1 = 0, i2 = 0;
        for (int i = 0; i < cnt; ++i)
        {
            cin >> x;
            v1.push_back(x);
        }
        for (int i = 0; i < cnt; ++i)
        {
            cin >> x;
            v2.push_back(x);
        }
        while (1)
        {
            if (i1 < cnt && i2 < cnt && v1[i1] == v2[i2]){
                i1++;
                i2++;
            }else if (s.size() && s.back() == v2[i2]){
                s.pop_back();
                i2++;
            }else{
                if (i1 == cnt){
                    break;
                }
                s.push_back(v1[i1++]);
            }
        }
        if (s.size()){
            cout << "No" << endl;
        }else{
            cout << "Yes" << endl;
        }
    }
    return 0;
}