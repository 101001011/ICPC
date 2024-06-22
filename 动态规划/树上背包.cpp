/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 总物品数量为 n, 构成森林结构. 每个物品依赖其父亲, 有重量和价值. 问 m 的背包空间最多能取到的价值.
Time Complexity: O(nm)
Hash Value: c5b42a6fb5a2a482
Date: 2024/6/22
Open Source License: GPL
*/

int n, m, dfn;
std::vector<std::vector<int>> E, f;
std::vector<int> w, v, siz;

void dfs (int u) {
    for (size_t v : E[u]) dfs(v), siz[u] += siz[v];
    dfn++;
    for (size_t j = 0; j <= m; j++) {
        f[dfn][j] = f[dfn - siz[u]][j];
        if (j >= w[u]) f[dfn][j] = std::max(f[dfn][j], f[dfn - 1][j - w[u]] + v[u]);
    }
}

int knapsack_on_tree () {
    siz = std::vector<int>(n + 1, 1);
    f = std::vector<std::vector<int>>(n + 2, std::vector<int>(m + 1));
    dfs(0);
    return f[n + 1][m];
}