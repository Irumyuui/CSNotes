#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int LEN = 1000005;
struct Trie{
    int nex[LEN][26], pos, ens[LEN];
    Trie(){
        pos = 0;
        memset(nex, 0, sizeof(nex));
        memset(ens, 0, sizeof(ens));
    }
    void insert(char *str){
        int len = strlen(str), p = 0;
        for (int i = 0; i < len; ++ i){
            int c = str[i] - 'a';
            if (nex[p][c] == 0){
                nex[p][c] = ++ pos;
            }
            p = nex[p][c];
        }
        ens[p] = 1;
    }
    int find(char *str){
        int len = strlen(str), p = 0;
        for (int i = 0; i < len; ++ i){
            int c = str[i] - 'a';
            if (nex[p][c] == 0){
                return 0;
            }
            p = nex[p][c];
        }
        if (ens[p] == 1){
            ens[p] = -1;
            return 1;
        }else{
            return -1;
        }
    }
};

Trie root;
int n;
char name[1115];

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin >> n;
    while (n --){
        cin >> name;
        root.insert(name);
    }
    cin >> n;
    while (n --){
        cin >> name;
        int res = root.find(name);
        if (res == 0){
            cout << "WRONG" << endl;
        }else if(res == 1){
            cout << "OK" << endl;
        }else{
            cout << "REPEAT" << endl;
        }
    }
    return 0;
}