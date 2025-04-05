#include <array>
#include <queue>
#include <tuple>
#include <vector>

class Solution {
   public:
    int trapRainWater(std::vector<std::vector<int>> &heightMap) {
        int n = heightMap.size();
        int m = heightMap[0].size();

        auto vis = std::vector(n, std::vector(m, false));
        auto heap = std::priority_queue<std::tuple<int, int, int>,
                                        std::vector<std::tuple<int, int, int>>,
                                        std::greater<>>();

        for (int x = 0; x < n; x++) {
            heap.emplace(heightMap[x][0], x, 0);
            heap.emplace(heightMap[x][m - 1], x, m - 1);
            vis[x][0] = vis[x][m - 1] = true;
        }
        for (int y = 1; y + 1 < m; y++) {
            heap.emplace(heightMap[0][y], 0, y);
            heap.emplace(heightMap[n - 1][y], n - 1, y);
            vis[0][y] = vis[n - 1][y] = true;
        }

        constexpr std::array<std::pair<int, int>, 4> dire = {
            std::pair{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        int ans = 0;

        while (!heap.empty()) {
            auto [h, x, y] = heap.top();
            heap.pop();
            for (auto [dx, dy] : dire) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
                    vis[nx][ny] = true;
                    ans += std::max(0, h - heightMap[nx][ny]);
                    heap.emplace(std::max(heightMap[nx][ny], h), nx, ny);
                }
            }
        }

        return ans;
    }
};