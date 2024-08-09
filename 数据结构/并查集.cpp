/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 维护并查集/带权并查集. type 为 1 表示带权, 否则不带权.
Time Complexity: O(m \alpha(n)).
Hash Value: e8575e085e4f98e1
Date: 2024/7/28
Open Source License: GPL
*/

class DSU {
private:
    bool type;
    int n;
    std::vector<int> fa, pnum, val;

    int _find(int x) {
        if (x != fa[x]) fa[x] = _find(fa[x]);
        return fa[x];
    }

    bool _merge(int x, int y) {
        int Rx = _find(x), Ry = _find(y);
        if (x != y) {
            if (pnum[Rx] < pnum[Ry])
                fa[Rx] = Ry, pnum[Ry] += pnum[Rx];
            else fa[Ry] = Rx, pnum[Rx] += pnum[Ry];
        }
        return Rx != Ry;
    }

    int find_(int x) {
        if (x != fa[x]) {
            int mark = fa[x];
            fa[x] = find_(fa[x]), val[x] += val[mark];
        }
        return fa[x];
    }

    bool merge_(int x, int y, int w) {
        int Rx = find_(x), Ry = find_(y);
        if (Rx == Ry) return (val[x] - val[y] == w);
        if (pnum[Rx] < pnum[Ry])
            fa[Rx] = Ry, pnum[Ry] += pnum[Rx], val[Rx] = val[y] + w - val[x];
        else fa[Ry] = Rx, pnum[Rx] += pnum[Ry], val[Ry] = val[x] - w - val[y];
        return true;
    }

public:
    DSU(int n, bool type): n(n), type(type) {
        for (int i = 0; i <= n; i++) fa.push_back(i);
        pnum = std::vector<int>(n + 1, 1);
        if (type) val.resize(n + 1);
    }

    int find(int u) {
        return type ? find_(u) : _find(u);
    }

    bool merge(int u, int v) {
        return _merge(u, v);
    }

    bool merge(int u, int v, int w) {
        return merge_(u, v, w);
    }
};