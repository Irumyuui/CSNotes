extern "C" int Seniorious(int x);

extern "C" int Chtholly(int n, int c) {
    int l = 1, r = n;

    int ans = n;
    while (l <= r && c) {
        int mid = l + ((r - l) >> 1);
        int check = Seniorious(mid);
        
        if (check >= 0) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }

        c --;
    }
    return ans;
}