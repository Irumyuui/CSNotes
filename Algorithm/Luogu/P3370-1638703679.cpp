#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int modp = 49999;
class HashS{
    public:
        vector<string>data[modp];
        int size;
        HashS(){
            size = 0;
        }
        int hash_key(const string &s){
            int key = 0;
            for (int i = 0; i < s.size(); ++ i){
                key = (key * i + (int)s[i] + i) % modp;
            }
            return key;
        }
        void insert(const string &s){
            int key = this->hash_key(s);
            for (auto it : this->data[key]){
                if (it == s){
                    return;
                }
            }
            this->data[key].push_back(s);
            this->size ++;
        }
};

HashS has;

int main(){
    std::ios::sync_with_stdio(false);
    //freopen("in.in", "r", stdin);
    int t;
    cin >> t;
    while (t --){
        string s;
        cin >> s;
        has.insert(s);
    }
    cout << has.size << endl;
    return 0;
}