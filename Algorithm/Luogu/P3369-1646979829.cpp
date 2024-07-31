#include <bits/stdc++.h>
using namespace std;
#define debug(x) std::cerr << #x << " " << x << std::endl;

class Treap {
    private:
        struct Node {
            int val, rank, size, cnt;
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
        int create(int val) {
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
    public:
        void inti(int size) {
            tr.assign(size + 1, Node());
            tr[0].child.assign(2, 0);
            tr[0].cnt = tr[0].size = tr[0].val = tr[0].rank = 0;
            tot = root = 0;
        }
        void insert(int &now, int val) {
            if (!now) {
                now = create(val);
                return;
            }
            if (tr[now].val == val) {
                tr[now].cnt ++;
            } else {
                int d = val < tr[now].val ? 0 : 1;
                insert(tr[now].child[d], val);
                if (tr[now] < tr[tr[now].child[d]]) {
                    rotate(now, d ^ 1);
                }
            }
            update(now);
        }
        void insert(int val) {
            insert(root, val);
        }
        void delet(int &now, int val) {
            if (!now) {
                return;
            }
            if (tr[now].val == val) {
                if (tr[now].cnt > 1) {
                    tr[now].cnt --;
                } else {
                    if (tr[now].child[0] && tr[now].child[1]) {
                        int d = tr[now].child[0] < tr[now].child[1] ? 0 : 1;
                        rotate(now, d ^ 1);
                        delet(tr[now].child[d ^ 1], val);
                    } else if (tr[now].child[0]) {
                        rotate(now, 1);
                        delet(tr[now].child[1], val);
                    } else if (tr[now].child[1]){
                        rotate(now, 0);
                        delet(tr[now].child[0], val);
                    } else {
                        now = 0;
                        return;
                    }
                }
            } else {
                int d = val < tr[now].val ? 0 : 1;
                delet(tr[now].child[d], val);
            }
            update(now);
        }
        void delet(int val) {
            delet(root, val);
        }
        int query_x_kth(int &now, int val) {
            if (!now) {
                return 0;
            }
            if (tr[now].val == val) {
                return tr[tr[now].child[0]].size + 1;
            } else if (val < tr[now].val) {
                return query_x_kth(tr[now].child[0], val);
            } else {
                return tr[tr[now].child[0]].size + tr[now].cnt + query_x_kth(tr[now].child[1], val);
            }
        }
        int query_x_kth(int val) {
            return query_x_kth(root, val);
        }
        int query_xthx(int &now, int kth) {
            if (!now) {
                return -1;
            }
            if (kth <= tr[tr[now].child[0]].size) {
                return query_xthx(tr[now].child[0], kth);
            } else if (kth <= tr[tr[now].child[0]].size + tr[now].cnt) {
                return tr[now].val;
            } else {
                return query_xthx(tr[now].child[1], kth - tr[now].cnt - tr[tr[now].child[0]].size);
            }
        }
        int query_xthx(int kth) {
            return query_xthx(root, kth);
        }
        void xpre(int now, int &ans ,int val) {
            if (!now) {
                return;
            }
            if (tr[now].val < val) {
                ans = tr[now].val;
                xpre(tr[now].child[1], ans, val);
            } else {
                xpre(tr[now].child[0], ans, val);
            }
        }
        int xpre(int val) {
            int ans = 0;
            xpre(root, ans, val);
            return ans;
        }
        void xnex(int now, int &ans, int val) {
            if (!now) {
                return;
            }
            if (tr[now].val > val) {
                ans = tr[now].val;
                xnex(tr[now].child[0], ans, val);
            } else {
                xnex(tr[now].child[1], ans, val);
            }
        }
        int xnex(int val) {
            int ans = 0;
            xnex(root, ans, val);
            return ans;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    Treap tr;
    tr.inti(int(1e6 + 10));
    while (n --) {
        int opt, x;
        cin >> opt >> x;

        if (opt == 1) {
            tr.insert(x);
        } else if (opt == 2) {
            tr.delet(x);
        } else if (opt == 3) {
            cout << tr.query_x_kth(x) << '\n';
        } else if (opt == 4) {
            cout << tr.query_xthx(x) << '\n';
        } else if (opt == 5) {
            cout << tr.xpre(x) << '\n';
        } else {
            cout << tr.xnex(x) << '\n';
        }
    }

    return 0;
}