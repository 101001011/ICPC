/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 将 n 拆分为若干个正整数的方案数.
Time Complexity: O(n\sqrt n)
Hash Value: ed28d53741bedf9b
Date: 2024/6/21
Open Source License: GPL
*/

template <unsigned int mod>
int number_of_ways_to_split_integer (int n) {
    size_t cnt = sqrt(n) + 1;
    std::vector<modint<mod>> f(n + 1);
    std::vector<std::vector<modint<mod>>>
      g(cnt, std::vector<modint<mod>>(n + 1));

    f[0] = g[0][0] = 1;
    for (size_t i = 1; i < cnt; i++)
        for (size_t j = i; j <= n; j++)
            f[j] += f[j - i];
    for (size_t i = 1; i < cnt; i++)
        for (size_t j = i; j <= n; j++){
            g[i][j] = g[i][j - i];
            if (j >= cnt) g[i][j] += g[i - 1][j - cnt];
        }

    modint<mod> ans(0);
    for (size_t i = 0; i <= n; i++)
        for (size_t k = 0; k < cnt; k++)
            ans += f[i] * g[k][n - i];
    return raw(ans);
}