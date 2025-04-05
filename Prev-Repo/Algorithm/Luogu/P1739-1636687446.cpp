#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    stack<char>st;
    string s;
    cin >> s;
    for (auto it : s)
        st.push(it);
    int no = 0, change = 0, ll = 0, rr = 0;
    while (!st.empty())
    {
        if (st.top() == ')'){
            rr ++;
        }else if (st.top() == '('){
            if (rr == 0){
                cout << "NO" << endl;
                return 0;
            }
            rr --;
        }
        st.pop();
    }
    if (rr == 0){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
    return 0;
}