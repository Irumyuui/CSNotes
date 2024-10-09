#include <span>
#include <utility>

void sift_down(std::span<int> a) {
    std::size_t p = 0, ch = p * 2 + 1;
    while (ch < a.size()) {
        if (ch + 1 < a.size() && a[ch] < a[ch + 1]) {
            ch++;
        }
        if (a[ch] < a[p]) {
            break;
        } else {
            std::swap(a[p], a[ch]);
            p = ch;
            ch = p * 2 + 1;
        }
    }
}

void heap_sort(std::span<int> a) {
    if (a.size() <= 1) {
        return;
    }

    int n = a.size();
    for (int i = (n - 2) / 2; i >= 0; i--) {
        sift_down(a.subspan(i));
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(a[0], a[i]);
        sift_down(a.first(i - 1));
    }
}