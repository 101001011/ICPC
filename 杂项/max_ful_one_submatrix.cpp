/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 悬线法求最大全 1 子矩阵.
Time Complexity: O(n^2).
Hash Value: d2e8c0d9b9d6f31
Date: 2024/6/21
Open Source License: GPL
*/

int max_ful_one_submatrix (const std::vector<std::vector<int>> &a) {
    size_t n = a.size(), m = a[0].size();
    std::vector<int> u(m);
    int res = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++)
            a[i][j] ? u[j]++ : u[j] = 0;
        std::vector<size_t> l(m), r(m);
        for (size_t j = 0; j < m; j++) l[j] = r[j] = j;
        for (size_t j = 0; j < m; j++)
            while (l[j] > 0 and u[l[j] - 1] >= u[j]) l[j] = l[l[j] - 1];
        for (size_t j = m - 1; j >= 0; j--)
            while (r[j] < m - 1 and u[r[j] + 1] >= u[j]) r[j] = r[r[j] + 1];
        for (size_t j = 0; j < m; j++)
            res = std::max(res, u[j] * (r[j] - l[j] + 1));
    }
    return res;
}