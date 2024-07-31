#include <iostream>
#include <vector>

using namespace std;

int number;
vector<int>path;
void dfs(int num, int sum)
{
    if (sum == number){
        int mark = 0;
        for (auto it : path)
        {
            if (mark == 1){
                cout << '+';
            }else{
                mark = 1;
            }
            cout << it;
        }
        cout << endl;
    }else if (sum > number){
        return;
    }else{
        for (int i = num; i < number; ++i)
        {
            if (sum + i > number){
                break;
            }
            path.push_back(i);
            dfs(i, sum + i);
        }
    }
    if (path.size()){
        path.pop_back();
    }
}


int main()
{
    cin >> number;
    dfs(1, 0);
    return 0;
}