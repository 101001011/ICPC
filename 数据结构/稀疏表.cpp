/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 稀疏表求静态区间并, 构造时需传入将两个元素并起来的函数, 如 `[](int x, int y) { return std::max(x, y); }`.
Time Complexity: O(n \log n) - O(1).
Hash Value: 7c60cdabae351c87
Date: 2024/7/28
Open Source License: GPL
*/

template <typename type>
class SparseTable {
private:
    int n, lg;
    std::function<type(type, type)> merge;
    std::vector<std::vector<type>> f;

public:
    SparseTable(std::vector<type> &a, std::function<type(type, type)> merge): merge(merge) {
        n = a.size(), lg = std::__lg(n);
        f = std::vector<std::vector<type>>(n, std::vector<type>(lg + 1));
        for (size_t i = 0; i < n; i++) f[i][0] = a[i];
        for (size_t j = 1; j <= lg; j++)
            for (size_t i = 0; i < n; i++)
                if (i + (1 << j - 1) < n)
                    f[i][j] = merge(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
                else f[i][j] = f[i][j - 1];
    }

    type qry(int l, int r) {
        int t = std::__lg(r - l + 1);
        return merge(f[l][t], f[r - (1 << t) + 1][t]);
    }
};