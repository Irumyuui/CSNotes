#include <bits/stdc++.h>
using namespace std;

class ODT {
    private:
        struct Node {
            int l, r;
            int val;
            Node(int l = 0, int r = 0, int val = 0) : l(l), r(r), val(val) {}
            bool operator < (const Node &a) const {
                return l < a.l;
            }
        };
        set<Node>tr;
    public:
        void insert(int l, int r, int val) {
            tr.insert(Node(l, r, val));
        }
        auto split(int pos) {
            auto it = tr.lower_bound(Node(pos));
            if (it != tr.end() && it->l == pos) {
                return it;
            }
            -- it;
            int l = it->l, r = it->r, val = it->val;
            tr.erase(it);
            tr.insert(Node(l, pos - 1, val));
            return tr.insert(Node(pos, r, val)).first;
        }
        void assign(int l, int r, int val) {
            auto end = split(r + 1), begin = split(l);
            tr.erase(begin, end);
            tr.insert(Node(l, r, val));
        }
        int query(int l, int r) {
            auto itr = split(r + 1), itl = split(l);
            set<int>cnt;
            for (; itl != itr; ++ itl) {
                cnt.insert(itl->val);
            }
            return cnt.size();
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t, o;
    cin >> n >> t >> o;
    
    ODT odt;
    odt.insert(1, n, 1);

    while (o --) {
        char ch;
        int l, r;
        cin >> ch >> l >> r;
        if (l > r) {
            swap(l, r);
        }
        if (ch == 'C') {
            int val;
            cin >> val;
            odt.assign(l, r, val);
        } else {
            cout << odt.query(l, r) << '\n';
        }
    }

    return 0;
}