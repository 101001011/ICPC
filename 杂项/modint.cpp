/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: modint 类, 可进行多数整数运算, 自动取模. 定义格式为 modint<998244353> x.
Time Complexity: O(1) ~ O(\log n)
Hash Value: 9c36a283a4a4c94
Date: 2024/6/12
Open Source License: GPL
*/

template <unsigned int mod>
class modint {
public:
    unsigned int val;
    modint() : val(0) {}
    template <typename type>
    modint(type x) : val((x % int(mod) + int(mod)) % int(mod)) {}
    modint operator- () const { return modint(mod - val); }
    modint inv() const { return assert(val), *this ^ ((int)(mod) - 2); }
    modint& operator+= (const modint &rhs) { if (val += rhs.val, val >= mod) val -= mod; return *this; }
    modint& operator-= (const modint &rhs) { return *this += -rhs; }
    modint& operator*= (const modint &rhs) { val = 1ull * val * rhs.val % mod; return *this; }
    modint& operator/= (const modint &rhs) { return *this *= rhs.inv(); }
    modint& operator^= (int k) { modint a = *this; *this = 1; for (; k; k >>= 1, a *= a) if (k & 1) *this *= a; return *this; }
    friend int raw (const modint &self) { return self.val; }
    friend modint operator+ (modint lhs, const modint &rhs) { return lhs += rhs; }
    friend modint operator- (modint lhs, const modint &rhs) { return lhs -= rhs; }
    friend modint operator* (modint lhs, const modint &rhs) { return lhs *= rhs; }
    friend modint operator/ (modint lhs, const modint &rhs) { return lhs /= rhs; }
    friend modint operator^ (modint lhs, const int &rhs) { return lhs ^= rhs; }
    friend bool operator== (const modint &lhs, const modint &rhs) { return lhs.val == rhs.val; }
    friend bool operator!= (const modint &lhs, const modint &rhs) { return lhs.val != rhs.val; }
    friend std::istream& operator>> (std::istream &is, modint &x) { int tmp; is >> tmp, x = tmp < 0 ? tmp + int(mod) : tmp; return is; }
    friend std::ostream& operator<< (std::ostream &os, modint x) { return os << x.val; }
};