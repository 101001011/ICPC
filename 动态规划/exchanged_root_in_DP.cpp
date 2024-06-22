/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 给定一棵树, 求一个结点, 满足以这个结点为根时所有结点的深度之和最大.
Time Complexity: O(n)
Hash Value: e6c1492e4216ade0
Date: 2024/6/22
Open Source License: GPL
*/

int n;
std::vector<std::vector<int>> E;
std::vector<int> siz;
std::vector<long long> sum, f;

void dfs (int u, int last) {
    for (size_t v : E[u]) if (v != last)
        dfs(v, u),
        siz[u] += siz[v],
        sum[u] += sum[v] + siz[v];
}

void calc (int u, int last) {
    for (size_t v : E[u]) if (v != last)
        f[v] = f[u] + n - 2 * siz[v],
        calc(v, u);
}

std::pair<int, long long> exchanged_root_in_DP () {
    siz = std::vector<int>(n + 1, 1);
    sum = f = std::vector<long long>(n + 1);
    dfs(1, 0);
    f[1] = sum[1], calc(1, 0);
    int idx;
    long long max = 0;
    for (int i = 1; i <= n; i++)
        if (f[i] > max) max = f[i], idx = i;
    return std::make_pair(idx, max);
}