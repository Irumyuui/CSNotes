#include <iostream>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int64_t a, b, p;
    std::cin >> a >> b >> p;
    auto qp = [](auto a, auto b, auto p) constexpr noexcept {
        using LL = decltype(a);
        LL ans=1,nw=a;
        while(b){
            LL get=b%3;
            LL getans=nw;
            LL getans2=1ll*nw*nw%p;
            if(get==0){
                nw=1ll*nw*getans2%p;
            }
            else if(get==1){
                ans=1ll*ans*nw%p;
                nw=1ll*nw*getans2%p;
            }
            else{
                ans=1ll*ans*getans2%p;
                nw=1ll*nw*getans2%p;
            }
            b/=3;
        }
        return ans;
    };
    std::cout << a << "^" << b << " mod " << p << "=" << qp(a, b, p);
}