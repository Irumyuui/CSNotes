#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int>v(n + 1, 0);
    for (int i = n; i >= 0; -- i)
        cin >> v[i];
    if (n == 0){
        cout << v[0];
        return 9;
    }
    if (v[n] != 0){
        if (v[n] == -1){
            cout << "-x";
        }else if (v[n] == 1){
            cout << "x";
        }else{
            cout << v[n] << "x";
        }
        if (n != 1){
            cout << "^" << n;
        }
    }
    for (int i = n - 1; i >= 0; -- i)
    {   if (i){
            if (v[i] > 0){
                cout << "+";
                if (v[i] != 1){
                    cout << v[i];
                }
            }else if (v[i] == 0){
                continue;
            }else if (v[i] < 0){
                if (v[i] != -1){
                    cout << v[i];
                }else{
                    cout << "-";
                }
            }
            cout << "x";
            if (i != 1){
                cout << "^" << i;
            }
        }else{
            if (v[i] != 0){
                printf("%+d", v[i]);
            }
        }
    }
    return 0;
}