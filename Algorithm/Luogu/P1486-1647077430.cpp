#include <bits/stdc++.h>
using namespace std;
#define all(x) std::begin(x), std::end(x)
using ll = long long;
using ill = __int128_t;
#ifndef ONLINE_JUDGE
#define debug(x) std::cerr << #x << " " << x << std::endl;
#else
#define debug(x)
#endif

class Treap {
    private:
        struct Node {
            ll val;
            int rank, size, cnt;
            vector<int>child;
            Node() {
                val = rank = size = cnt = 0;
            }
            bool operator < (const Node &a) const {
                return rank < a.rank;
            }
            bool operator > (const Node &a) const {
                return rank > a.rank;
            }
        };
        vector<Node>tr;
        int tot, root;
        int create(ll val) {
            int now = ++ tot;
            tr[now].child.assign(2, 0);
            tr[now].val = val;
            tr[now].size = tr[now].cnt = 1;
            tr[now].rank = rand();
            return now;
        }
        void update(int now) {
            tr[now].size = tr[tr[now].child[0]].size + tr[tr[now].child[1]].size + tr[now].cnt;
        }
        void rotate(int &now, int d) {
            int tmp = tr[now].child[d ^ 1];
            tr[now].child[d ^ 1] = tr[tmp].child[d];
            tr[tmp].child[d] = now;
            update(now);
            update(tmp);
            now = tmp;
        }
        void insert(int &now, ll val) {
            if (!now) {
                now = create(val);
                return;
            }
            if (tr[now].val == val) {
                tr[now].cnt ++;
            } else {
                int d = val < tr[now].val ? 1 : 0;
                insert(tr[now].child[d], val);
                if (tr[now] < tr[tr[now].child[d]]) {
                    rotate(now, d ^ 1);
                }
            }
            update(now);
        }
        bool getkth(int &now, ll kth, ll &ans) {
            if (!now) {
                return false;
            }
            if (kth <= tr[tr[now].child[0]].size) {
                return getkth(tr[now].child[0], kth, ans);
            } else if (kth <= tr[tr[now].child[0]].size + tr[now].cnt) {
                ans = tr[now].val;
                return true;;
            } else {
                return getkth(tr[now].child[1], kth - tr[now].cnt - tr[tr[now].child[0]].size, ans);
            }
        }
        void del(int &now, ll k, ll &lev) {
            if (!now)
                return;
            while (now && tr[now].val + k < 0) {
                lev += tr[now].cnt + tr[tr[now].child[1]].size;
                now = tr[now].child[0];
            }
            del(tr[now].child[1], k, lev);
            update(now);
        }
    public:
        void inti(int size) {
            tr.assign(size + 1, Node());
            tr[0].child.assign(2, 0);
            tr[0].cnt = tr[0].size = tr[0].val = tr[0].rank = 0;
            tot = root = 0;
        }
        void insert(ll val) {
            insert(root, val);
        }
        bool getkth(ll kth, ll &ans) {
            return getkth(root, kth, ans);
        }
        void del(const ll &k, ll &lev) {
            del(root, k, lev);
        }
};

int n;
ll mlim, k;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    cin >> n >> mlim;
    Treap tr;
    tr.inti(1e6 + 10);
    ll lev = 0;

    for (int i = 1; i <= n; ++ i) {
        char opt;
        cin >> opt;

        if (opt == 'I') {
            ll x;
            cin >> x;
            if (x - mlim >= 0) {
                tr.insert(x - mlim - k);
            }
        } else if (opt == 'A') {
            ll x;
            cin >> x;
            k += x;
        } else if (opt == 'S') {
            ll x;
            cin >> x;
            k -= x;
            tr.del(k, lev);
        } else {
            ll kth, ans;
            cin >> kth;
            if (tr.getkth(kth, ans)) {
                cout << ans + k + mlim << '\n';
            } else {
                cout << "-1\n";
            }
        }
    }
    cout << lev;
    
    return 0;
}