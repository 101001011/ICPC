/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 求 0/1 背包的最优方案数, 调用方式为 count<mod> (w, v, m), 返回方案数对 mod 取模的值.
Time Complexity: O(nm)
Hash Value: 23a09bcedd8a1dbe
Date: 2024/6/12
Open Source License: GPL
*/

template <unsigned int mod>
int count (const std::vector<int> &w, const std::vector<int> &v, int m) {
    size_t n = w.size();
    std::vector<int> f(m + 1);
    std::vector<modint<mod>> cnt(m + 1);
    f[0] = 0, cnt[0] = 1;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = m; j >= w[i]; j--) {
            int tmp = std::max(f[j], f[j - w[i]] + v[i]);
            modint<mod> sum = 0;
            if (tmp == f[j]) sum += cnt[j];
            if (tmp == f[j - w[i]] + v[i]) sum += cnt[j - w[i]];
            f[j] = tmp, cnt[j] = sum;
        }
    }

    int Max = 0;
    modint<mod> res = 0;
    for (size_t i = 0; i <= m; i++) Max = std::max(Max, f[i]);
    for (size_t i = 0; i <= m; i++)
        if (f[i] == Max) res += cnt[i];
    return raw(res);
}