#include <iostream>

int main() {
    int l = 1, r = 1e9;

    int ans = r, cnt = 50;
    while (l <= r && cnt) {
        int mid = l + ((r - l) >> 1);
        std::cout << mid << std::endl;
        
        int res;
        std::cin >> res;

        if (res >= 0) {
            ans = mid;
            r = mid - 1;
            
            if (res == 0) {
                break;
            }
        } else {
            l = mid + 1;
        }

        -- cnt;
    }

    std::cout << ans << std::endl;

    return 0;
}