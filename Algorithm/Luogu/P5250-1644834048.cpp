#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int t;
    cin >> t;

    set<int>wood;

    while (t --){
        int c, k;
        cin >> c >> k;

        if (c == 1){
            if (wood.count(k)){
                cout << "Already Exist\n";
            }else{
                wood.insert(k);
            }
        }else{
            if (wood.empty()){
                cout << "Empty\n";
            }else{
                auto it = wood.lower_bound(k);
                if (it == wood.end()){
                    cout << *(-- it) << '\n';
                }else if (it == wood.begin()){
                    cout << *it << '\n';
                }else{
                    auto it_ = it --;
                    if (abs(*it - k) <= abs(*it_ - k)){
                        cout << *it << '\n';
                    }else{
                        cout << *it_ << '\n';
                        it = it_;
                    }
                }
                wood.erase(it);
            }
        }
    }

    return 0;
}