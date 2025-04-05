#include <bits/stdc++.h>
using namespace std;

class DST {
private:
    std::vector<int> dst;
    int cnt;
public:
    DST(int size) : dst(size + 1, -1), cnt(size) {}
    void init(int size) {
        dst.assign(size + 1, -1);
        cnt = size;
    } 
    int& operator [] (int id) {
        return dst[id];
    }
    int Find(int id) {
        if (dst[id] > 0) {
            return dst[id] = Find(dst[id]);
        }
        return id;
    }
    bool Union(int a, int b) {
        a = Find(a); b = Find(b);
        if (a == b) return false;
        dst[a] += dst[b];
        dst[b] = a;
        cnt --;
        return true;
    }
    bool same(int a, int b) {
        return Find(a) == Find(b);
    }
    int count() const {
        return cnt;
    }
    int count(int id) {
        int d = Find(id);
        return -dst[d];
    }
};

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, q;
	cin >> n >> q;
	DST dst(n * 3);
	int cnt = 0;
	while (q --) {
		int c, a, b;
		cin >> c >> a >> b;
		if (a > n || b > n) {
			cnt ++;
		} else if (c == 1) {
			if (dst.Find(a + n) == dst.Find(b) || dst.Find(a) == dst.Find(b + n)
				|| dst.Find(a + n * 2) == dst.Find(b + n) || dst.Find(a + n) == dst.Find(b + n * 2)
				) {
				cnt ++;
			} else {
				dst.Union(a, b);
				dst.Union(a + n, b + n);
				dst.Union(a + n * 2, b + n * 2);
			}
		} else {
			if ( a == b || dst.Find(a) == dst.Find(b)
				|| dst.Find(a + n) == dst.Find(b + n)
				|| dst.Find(a + n * 2) == dst.Find(b + n * 2)
				|| dst.Find(b) == dst.Find(a + n * 2)
				|| dst.Find(b + n) == dst.Find(a)
				|| dst.Find(b + n * 2) == dst.Find(a + n)
				) {
				cnt ++;
			} else {
				dst.Union(b, a + n);
				dst.Union(b + n, a + n * 2);
				dst.Union(b + n * 2, a);
			}
		}
	}
	cout << cnt << '\n';
}