#include <ostream>
#include <utility>

class Complex {
    private:
        double re, im;
    public:
        Complex() : re(0), im(0) {}
        template<typename T> Complex(const T &re = {}, const T &im = {}) : re(re), im(im) {}
        Complex(const Complex &a) : Complex(a.real(), a.imag()) {};
        
        const double real() const {
            return re;
        }
        const double imag() const {
            return im;
        }
        void real(const Complex &a) {
            re = a.real();
        }
        template<typename T> void real(const T &val) {
            re = val;
        }
        void imag(const Complex &x) {
            im = x.imag();
        }
        template<typename T> void imag(const T &val) {
            im = val;
        }

        Complex operator + (const Complex &a) const {
            return Complex(re + a.real(), im + a.imag());
        }
        const Complex &operator += (const Complex &a) {
            re += a.real();
            im += a.imag();
            return *this;
        }
        template<typename T> const Complex &operator += (const T &val) {
            re += val;
            return *this;
        }

        Complex operator - (const Complex &a) const {
            return Complex(re - a.real(), im - a.imag());
        }
        const Complex &operator -= (const Complex &a) {
            re -= a.real();
            im -= a.imag();
            return *this;
        }
        template<typename T> const Complex &operator -= (const T &val) {
            re -= val;
            return *this;
        }

        Complex operator * (const Complex &a) const {
            return Complex(re * a.real() - im * a.imag(), re * a.imag() + im * a.real());
        }
        const Complex &operator *= (const Complex &a) {
            return *this *= a;
        }
        template<typename T> const Complex &operator *= (const T &val) {
            re *= val;
            im *= val;
            return *this;
        }

        Complex operator / (const Complex &a) const {
            double tmp = a.real() * a.real() + a.imag() * a.imag();
            return Complex((re * a.real() + im * a.imag()) / tmp, (im * a.real() - re * a.imag()) / tmp);
        }
        const Complex &operator /= (const Complex &a) {
            return *this = *this / a;
        }
        template<typename T> const Complex &operator /= (const T &val) {
            re /= val;
            im /= val;
            return *this;
        }

        friend std::ostream &operator << (std::ostream &out, const Complex &x) {  // 输出
            out << '(' << x.real() << ',' << x.imag() << ')';
            return out;
        }
};

// #include <bits/stdc++.h>
// using namespace std;

// int main() {

//     Complex a(2, 2);
//     Complex b(3, -1);

//     complex<double> x(2, 2), y(3, -1);

//     // cout << b / a << ' ' << y / x << '\n';
//     // b /= a; y /= x;
//     // b /= 2;
//     // y /= 2;
//     cout << b << ' ' << y << '\n';
    

//     return 0;
// }

/*

#include <utility>
#include <ostream>
#include <cmath>

class Complex {
    private:
        double re, im;  // real and imag
    public:
        // 构造函数
        Complex() : re(0), im(0) {}
        // template<typename T> Complex(const T &re = 0) : re(re), im(0) {};
        Complex(const Complex &a) : re(a.real()), im(a.imag()) {};
        template<typename T> Complex(const T &re = {}, const T &im = {}) : re(re), im(im) {};
        // 实部与虚部
        template<typename T> void real(const T &val);  // 更改实部
        template<typename T> void imag(const T &val);  // 更改虚部
        const double real() const;  // 返回实部
        const double imag() const;  // 返回虚部
        // 复数加法
        Complex operator + (const Complex &a) const;
        template<typename T> Complex operator + (const T &val) const;
        const Complex &operator += (const Complex &a);
        template<typename T> const Complex &operator += (const T &val);
        // 复数减法
        Complex operator - (const Complex &a) const;
        template<typename T> Complex operator - (const T &val) const;
        const Complex &operator -= (const Complex &a);
        template<typename T> const Complex &operator -= (const T &val);
        // 复数乘法
        Complex operator * (const Complex &a) const;
        template<typename T> Complex operator * (const T &val) const;
        const Complex &operator *= (const Complex &a);
        template<typename T> const Complex &operator *= (const T &val);
        // 复数除法
        Complex operator / (const Complex &a) const;
        template<typename T> Complex operator / (const T &val) const;
        const Complex &operator /= (const Complex &a);
        template<typename T> const Complex &operator /= (const T &val);
        // 杂项
        void swap(Complex &x);  // 交换两个复数
        double abs();  // 复数的模
        friend std::ostream &operator << (std::ostream &out, const Complex &x) {  // 输出
            out << '(' << x.real() << ',' << x.imag() << ')';
            return out;
        }
};

template<typename T> void Complex::real(const T &val) {
    re = val;
}
template<typename T> void Complex::imag(const T &val) {
    im = val;
}
const double Complex::real() const {
    return re;
}
const double Complex::imag() const {
    return im;
}

Complex Complex::operator + (const Complex &a) const {
    return Complex(re + a.real(), im + a.imag());
}
template<typename T> Complex Complex::operator + (const T &val) const {
    return Complex(re + val, im);
}
const Complex &Complex::operator += (const Complex &a){
    re += a.real();
    im += a.imag();
    return *this;
}
template<typename T> const Complex &Complex::operator += (const T &val) {
    re += val;
    return *this;
}

Complex Complex::operator - (const Complex &a) const {
    return Complex(re - a.real(), im - a.imag());
}
template<typename T> Complex Complex::operator - (const T &val) const {
    return Complex(real() - val, imag());
}
const Complex &Complex::operator -= (const Complex &a){
    re -= a.real();
    im -= a.imag();
    return *this;
}
template<typename T> const Complex &Complex::operator -= (const T &val) {
    re -= val;
    return *this;
}

Complex Complex::operator * (const Complex &a) const {
    return Complex(re * a.real() - im * a.imag(), re * imag() + im * a.real());
}
template<typename T> Complex Complex::operator * (const T &val) const {
    return Complex(re * val, im * val);
}
const Complex &Complex::operator *= (const Complex &a) {
    *this = *this * a;
    return *this;
}
template<typename T> const Complex &Complex::operator *= (const T &val) {
    *this = *this * val;
    return *this;
}

Complex Complex::operator / (const Complex &a) const {
    double tmp = a.real() * a.real() + a.imag() * a.imag();
    return Complex((re * a.real() + im * a.imag()) / tmp, (im * a.real() - re * a.imag()) / tmp);
}
template<typename T> Complex Complex::operator / (const T &val) const {
    return Complex(re / val, im / val);
}
const Complex &Complex::operator /= (const Complex &a) {
    *this = *this / a;
    return this;
}
template<typename T> const Complex &Complex::operator /= (const T &val) {
    *this = *this / val;
    return *this;
}

void Complex::swap(Complex &x) {
    Complex tmp = std::move(x);
    x = std::move(*this);
    *this = std::move(tmp);
}

double Complex::abs() {
    return std::hypot(re, im);
}

*/

#include <bits/stdc++.h>
using namespace std;
#define all(x) std::begin(x), std::end(x)

using cd = Complex;
const double PI = acos(-1);

int n, m;
void fft(vector<cd>&a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++ i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        double k = 2 * PI / len * (inv ? -1 : 1);
        cd wn(cos(k), sin(k));
        for (int i = 0; i < n; i += len) {
            cd wk(1, 0);
            for (int j = 0; j < len / 2; ++ j) {
                cd x = a[i + j], y = a[i + j + len / 2] * wk;
                a[i + j] = x + y;
                a[i + j + len / 2] = x - y;
                // wk *= wn;
                wk = wk * wn;
            }
        }
    }
    if (inv) {
        for (auto &x : a) 
            x /= n;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n >> m;
    int len = 1;
    while (len <= n + m) {
        len <<= 1;
    }
    vector<cd>a(len, cd(0)), b(len, cd(0)), c(len, cd(0));
    for (int i = 0; i <= n; ++ i) {
        int x; 
        cin >> x;
        a[i].real(x);
    }
    for (int j = 0; j <= m; ++ j) {
        int x;
        cin >> x;
        b[j].real(x);
    }
    fft(a, false); fft(b, false);
    for (int i = 0; i < len; ++ i) {
        c[i] = a[i] * b[i];
    }
    fft(c, true);
    for (int i = 0; i <= n + m; ++ i) {
        int x = c[i].real() + 0.5;
        cout << x << ' ';
    }

    return 0;
}