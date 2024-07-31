#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;

template <class T> inline void read(T &val) {
    T x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    val = x * f;
}
template <class T, class... Args> inline void read(T &val, Args&... args) {
    read(val); read(args...);
}

const int N = 1e5 + 1;
int cnt[N];
queue<ll> q1, q2;

int main() {
	int n;
	read(n);
	for (int i = 1; i <= n; ++ i) {
		int x;
		read(x);
		cnt[x] ++;
	}
	for (int i = 0; i < N; ++ i) {
		while (cnt[i]) {
			cnt[i] --;
			q1.push(i);
		}
	}
	auto get = [&q1 = q1, &q2 = q2]() {
		ll ret = 0;
		if (!q1.empty() && !q2.empty()) {
			if (q1.front() < q2.front()) {
				ret = q1.front();
				q1.pop();
			} else {
				ret = q2.front();
				q2.pop();
			}
		} else if (!q1.empty()) {
			ret = q1.front();
			q1.pop();
		} else if (!q2.empty()) {
			ret = q2.front();
			q2.pop();
		}
		return ret;
	};
	ll ans = 0;
	for (int i = 1; i < n; ++ i) {
		ll a = get(), b = get();
		ans += a + b;
		q2.push(a + b);
	}
	printf("%lld", ans);
}