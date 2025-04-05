#if defined(_MSC_VER)
#define _MSVC_TESTING_NVCC
#include <__msvc_all_public_headers.hpp>
#else
#include <bits/stdc++.h>
#endif

#if !defined(ONLINE_JUDGE) || defined(LOCAL_JUDGE)
#include "debug.hpp"
#else
#define debug(...)

#endif

using i64 = std::int64_t;

template <typename T, typename Comp = std::greater<T>>
using Heap = std::priority_queue<T, std::vector<T>, Comp>;

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

void Main() {
    int n, m;
    std::cin >> n >> m;

    debug(1);

    std::vector a(n + 2, std::vector<char>(m + 2));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> a[i][j];
        }
    }

    std::vector vis(n + 2, std::vector<bool>(m + 2));
    for (int i = 0; i < m + 2; i++) {
        vis[0][i] = vis.back()[i] = true;
    }
    for (int i = 0; i < n + 2; i++) {
        vis[i].front() = vis[i].back() = true;
    }

    debug(2);

    constexpr std::array<std::pair<int, int>, 4> DIR = {
        std::pair{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int ans = 0;

    for (int x = 1, y = 1; !vis[x][y]; x++, y++) {
        std::vector<char> seq;
        seq.reserve(n * m);
        std::queue<std::tuple<int, int, int>> q;
        q.emplace(std::tuple{x, y, 0});

        while (!q.empty()) {
            auto [x, y, d] = q.front();
            q.pop();
            vis[x][y] = true;
            seq.emplace_back(a[x][y]);

            int nx = x + DIR[d].first, ny = y + DIR[d].second;
            if (vis[nx][ny]) {
                if (d + 1 == DIR.size()) {
                    break;
                }
                d++;
                // (d += 1) %= DIR.size();
                nx = x + DIR[d].first, ny = y + DIR[d].second;
            }

            if (!vis[nx][ny]) {
                q.emplace(std::tuple{nx, ny, d});
            }
        }

        debug(x, y, seq);
        for (int i = 0; i < std::min<int>(3, seq.size()); i++) {
            seq.emplace_back(seq[i]);
        }
        debug(seq);

        int cnt = 0;
        for (int i = 3; i < seq.size(); i++) {
            if (seq[i - 3] == '1' && seq[i - 2] == '5' && seq[i - 1] == '4' &&
                seq[i] == '3') {
                cnt++;
            }
        }

        debug(cnt);
        ans += cnt;
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test_cast = 1;
    std::cin >> test_cast;
    for (int test = 1; test <= test_cast; test++) {
        debug(test);
        Main();
    }
}