/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 求一棵树的点分治树.
Time Complexity: O(n \log n).
Hash Value: b5ec6915551793
Date: 2024/8/1
Open Source License: GPL
*/

class DivideTree {
private:
    int n;
    std::vector<std::vector<int>> E;
    std::vector<int> max, siz;
    std::vector<bool> vis;

    void updsiz(int u, int last) {
        siz[u] = 1;
        for (int v : E[u]) if (v != last and not vis[v])
            updsiz(v, u), siz[u] += siz[v];
    }

    void find(int u, int last, int m, int &rt) {
        siz[u] = 1, max[u] = 0;
        for (int v : E[u]) if (v != last and not vis[v]) {
            find(v, u, m, rt), siz[u] += siz[v];
            max[u] = std::max(max[u], siz[v]);
        }
        max[u] = std::max(max[u], m - siz[u]);
        if (max[u] < max[rt]) rt = u;
    }

    void build(int u, int last) {
        vis[u] = true;
        for (int v : E[u]) if (v != last and not vis[v]) {
            int rt = 0;
            find(v, u, siz[v], rt), updsiz(rt, u);
            T[u].push_back(rt), T[rt].push_back(u);
            build(rt, u);
        }
    }

public:
    int root;
    std::vector<std::vector<int>> T;

    DivideTree(std::vector<std::vector<int>> E): E(E), root(0) {
        n = E.size();
        T.resize(n), max.resize(n), siz.resize(n), vis.resize(n);
        max[0] = n;
        find(1, 0, n - 1, root), updsiz(root, 0);
        build(root, 0);
    }
};