/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 树链剖分求 LCA.
Time Complexity: O(n) - O(\log n).
Hash Value: fa8604275f54f949
Date: 2024/7/29
Open Source License: GPL
*/

class HeavyLight_Decomposition_LCA {
private:
    int n, rt;
    std::vector<std::vector<int>> E;
    std::vector<int> fa, dep, siz, top, son;

    void dfs1(int u, int last) {
        fa[u] = last, dep[u] = dep[last] + 1, siz[u] = 1;
        for (int v : E[u]) if (v != last) {
            dfs1(v, u), siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }

    void dfs2(int u, int t) {
        top[u] = t;
        if (son[u]) dfs2(son[u], t);
        for (int v : E[u])
            if (v != fa[u] and v != son[u]) dfs2(v, v);
    }

public:
    HeavyLight_Decomposition_LCA(std::vector<std::vector<int>> &E, int rt): E(E), rt(rt) {
        n = E.size();
        fa.resize(n), dep.resize(n), siz.resize(n), top.resize(n), son.resize(n);
        dfs1(rt, 0), dfs2(rt, rt);
    }

    int LCA(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};