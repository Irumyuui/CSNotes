#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    priority_queue<int, vector<int>, greater<int>>q;
    int n;
    cin >> n;
    while (n --)
    {
        int op, x;
        cin >> op;
        if (op == 1){
            cin >> x;
            q.push(x);
        }else if (op == 2){
            cout << q.top() << endl;
        }else{
            q.pop();
        }
    }
    return 0;
}