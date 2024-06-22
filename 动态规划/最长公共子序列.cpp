/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 求两个序列的最长公共子序列.
Time Complexity: O(nm / w = 63)
Hash Value: 6149eac659ce7fb7
Date: 2024/6/12
Open Source License: GPL
*/

template <typename type>
int lcs (std::vector<type> a, std::vector<type> b) {
    std::vector<type> values = discretize({&a, &b}); // 定义见离散化模块.
    size_t n = a.size(), m = b.size();
    std::vector<unsigned long long> M(n / 63 + 1);
    std::vector<std::vector<unsigned long long>>
        p(values.size(), std::vector<unsigned long long>(n / 63 + 1));

    for (size_t i = 0; i < n; i++)
        p[a[i]][i / 63] |= 1ull << (i % 63);
    for (size_t i = 0; i < m; i++) {
        unsigned long long t = 1;
        for (size_t j = 0; j <= n / 63; j++) {
            unsigned long long x = M[j], y = x | p[b[i]][j];
            x = 2 * x + t + (((1ull << 63) - 1) ^ y);
            M[j] = x & y, t = x >> 63;
        }
    }

    int ans = 0;
    for (size_t j = 0; j <= n / 63; j++)
        ans += __builtin_popcountll(M[j]);
    return ans;
};