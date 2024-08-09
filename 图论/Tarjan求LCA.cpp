/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 离线 Tarjan 算法求 LCA.
Time Complexity: O(n + m). 
Hash Value: 769333207eb2f053
Date: 2024/7/28
Open Source License: GPL
*/

class TarjanLCA {
private:
    class DSU {
    private:
        int n;
        std::vector<int> fa, pnum, top;

        int find(int x) {
            if (x != fa[x]) fa[x] = find(fa[x]);
            return fa[x];
        }

    public:
        DSU(int n): n(n) {
            for (int i = 0; i <= n; i++)
                fa.push_back(i), top.push_back(i);
            pnum = std::vector<int>(n + 1, 1);
        }

        bool merge(int x, int y) {
            int Rx = find(x), Ry = find(y);
            if (x != y) {
                if (pnum[Rx] < pnum[Ry])
                    fa[Rx] = Ry, pnum[Ry] += pnum[Rx];
                else fa[Ry] = Rx, pnum[Rx] += pnum[Ry];
                top[Rx] = top[Ry];
            }
            return Rx != Ry;
        }

        int shallow(int x) {
            return top[find(x)];
        }
    };

    int n, m, rt, cnt;
    std::vector<std::vector<int>> E, q;
    std::vector<bool> vis;
    std::vector<int> dfn;
    std::vector<std::pair<int, int>> p;
    DSU *dsu;

    void calc(int u, int last) {
        dfn[u] = ++cnt;
        for (int v : E[u]) if (v != last) calc(v, u);
        cnt++;
        for (int i : q[u]) {
            int v = v = p[i].first + p[i].second - u;
            if (dfn[v] >= dfn[u] and dfn[v] <= cnt) ans[i] = u;
        }
    }

    void dfs(int u, int last) {
        vis[u] = true;
        for (int i : q[u]) {
            int v = p[i].first + p[i].second - u;
            if (not ans[i] and vis[v]) ans[i] = dsu->shallow(v);
        }
        for (int v : E[u]) if (v != last) dfs(v, u);
        if (u != rt) dsu->merge(u, last);
    }

public:
    std::vector<int> ans;

    TarjanLCA(std::vector<std::vector<int>> &E, int rt, std::vector<std::pair<int, int>> &p): E(E), rt(rt), p(p) {
        n = E.size(), m = p.size(), cnt = 0;
        q.resize(n + 1), vis.resize(n + 1), dfn.resize(n + 1), ans.resize(m);
        for (int i = 0; i < p.size(); i++)
            q[p[i].first].push_back(i),
            q[p[i].second].push_back(i);
        dsu = new DSU(n);
        calc(rt, 0), dfs(rt, 0);
    }
};