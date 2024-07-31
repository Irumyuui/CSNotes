#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

map<string, int>msi;

int main()
{
    int n;
    cin >> n;
    getchar();
    while (n --)
    {
        string name;
        cin >> name;
        msi[name] = 0;
    }
    cin >> n;
    getchar();
    while (n --)
    {
        string name;
        cin >> name;
        auto it = msi.find(name);
        if (it != msi.end()){
            if (msi[name] == 0){
                cout << "OK" << endl;
                msi[name] ++;
            }else{
                cout << "REPEAT" << endl;
            }
        }else{
            cout << "WRONG" << endl;
        }
        
    }
    return 0;
}