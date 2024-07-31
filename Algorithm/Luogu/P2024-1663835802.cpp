#include <iostream>
#include <string>
#include <cstring>

#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

using namespace std;
#define nullptr NULL
void Solution();
int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
	return 0;
}

const int N = 5e4 + 10;
int dad[N * 3];

int find(int x) {
	debug(x);
	if (dad[x] == -1) {
		return x;
	}
	return dad[x] = find(dad[x]);
}
bool merge(int a, int b) {
	a = find(a); b = find(b);
	if (a == b) return false;
	dad[b] = a;
	return true;
}

bool same(int a, int b) {
	return find(a) == find(b);
}

void Solution() {
	memset(dad, -1, sizeof(dad));
	int n, q;
	cin >> n >> q;
	int fake = 0;
	for (int _ = 0; _ < q; ++ _) {
		int d, x, y;
		cin >> d >> x >> y;
		debug(d, x, y, fake);
		if (x > n || y > n) {
			fake ++;
			continue;
		}
		// 1 - n := A; n+1 - 2*n := B; 2*n+1 - 3*n := C
		if (d == 1) {
			if (x == y) {
				continue;
			}
			if (same(x, y + n * 2) || same(x + n, y) || same(x + 2 * n, y + n) || same(x + n * 2, y) || same(x, y + n) || same(x + n, y + 2 * n)) {
				fake ++;
			} else {
				merge(x, y);
				merge(x + n, y + n);
				merge(x + 2 * n, y + 2 * n);
			}
		} else {
			if (x == y) {
				fake ++;
				continue;
			}
			if (same(x, y) || same(x + n, y + n) || same(x + n * 2, y + n * 2) || same(x, y + n * 2) || same(x + n, y) || same(x + 2 * n, y + n)) {
				fake ++;
			} else {
				merge(x, y + n);
				merge(x + n, y + 2 * n);
				merge(x + 2 * n, y);
			}
		}
	}
	cout << fake << '\n';
}