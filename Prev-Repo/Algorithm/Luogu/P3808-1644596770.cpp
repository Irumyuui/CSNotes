#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e6 + 10, MAXCHAR = 26;
int child[N][MAXCHAR + 1];
int val[N];

inline int getnex(char ch){return int(ch - 'a');}

struct Trie{
    int tot;

    Trie(){
        tot = 1;
        memset(child, 0, sizeof(child));
        memset(val, 0, sizeof(val));
    }
    
    void insert(char *str){
        int self = 0, len = std::strlen(str);

        for (int i = 0; i < len; ++ i){
            int nex = getnex(str[i]);

            if (child[self][nex] == 0){
                child[self][nex] = tot ++;
            }

            self = child[self][nex];
        }

        val[self] ++;
    }
}trie;

int last[N], fail[N];
void getfail(){
    queue<int>q;
    fail[0] = 0;

    for (int ch = 0; ch < MAXCHAR; ++ ch){
        int nex = child[0][ch];
        if (nex){
            fail[nex] = 0;
            q.push(nex);
            last[nex] = 0;
        }
    }

    while (!q.empty()){
        int self = q.front();
        q.pop();

        for (int ch = 0; ch < MAXCHAR; ++ ch){
            int nex = child[self][ch];
            
            if (!nex){
                child[self][ch] = child[fail[self]][ch];
                continue;
            }

            q.push(nex);

            int before = fail[self];
            while (before && !child[before][ch]){
                before = fail[before];
            }

            fail[nex] = child[before][ch];
            last[nex] = val[fail[nex]] ? fail[nex]: last[fail[nex]];
        }
    }
}

int find(char *str){
    int len = std::strlen(str), self = 0, ans = 0;
    
    for (int i = 0; i < len; ++ i){
        self = child[self][getnex(str[i])];

        int node = self;
        while (node && val[node]){
            ans += val[node];
            val[node] = 0;
            node = fail[node]; 
        }
    }

    return ans;
}

char str[N];

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;

    while (n --){
        cin >> str;
        trie.insert(str);
    }
    getfail();

    cin >> str;

    cout << find(str);

    return 0;
}