#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    map<int, int>wood;

    int t;
    cin >> t;

    int cnt = 0;

    while (t --){
        int c, k;
        cin >> c >> k;

        if (c == 1){
            wood[k] ++;

            if (wood[k] >= 2){
                cout << "Already Exist\n";
                wood[k] --;
            }
            
        }else{
            if (wood.empty()){
                cout << "Empty\n";
                continue;
            }            

            auto it = wood.lower_bound(k);

            if (it == wood.end()){
                cout << (-- it)->first << '\n';
                it->second --;

                if (it->second == 0){
                    wood.erase(it);
                }
            }else if (it == wood.begin()){
                cout << it->first << '\n';
                it->second --;

                if (it->second == 0){
                    wood.erase(it);
                }
            }else{
                auto itb = it;
                auto ita = -- it;

                if (abs(ita->first - k) <= abs(itb->first - k)){
                    cout << ita->first << '\n';
                    it = ita;
                }else{
                    cout << itb->first << '\n';
                    it = itb;
                }

                it->second --;
                if (it->second == 0){
                    wood.erase(it);
                }
            }
        }
    }

    return 0;
}