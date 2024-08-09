/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 求出树的欧拉序, 进而将 LCA 问题转化为 RMQ 问题解决.
Time Complexity: O(n) - O(1).
Hash Value: a87b80df9009052e
Date: 2024/7/29
Open Source License: GPL
*/

class LCAtoRMQ {
private:
    int n, rt;
    std::vector<std::vector<int>> E;
    std::vector<int> dep, pos;
    std::vector<std::pair<int, int>> eul;
    RMQ<std::pair<int, int>> *seq;  // 定义见 RMQ.

    void dfs(int u, int last) {
        dep[u] = dep[last] + 1;
        eul.push_back(std::make_pair(dep[u], u));
        if (not pos[u]) pos[u] = eul.size() - 1;
        for (int v : E[u]) if (v != last)
            dfs(v, u), eul.push_back(std::make_pair(dep[u], u));
    }

public:
    LCAtoRMQ(std::vector<std::vector<int>> E, int rt): E(E), rt(rt) {
        n = E.size() - 1;
        dep.resize(n + 1), pos.resize(n + 1);
        dfs(rt, 0);
        seq = new RMQ<std::pair<int, int>>(eul,
          [](std::pair<int, int> x, std::pair<int, int> y) {
            return std::min(x, y);
        });
    }

    int LCA(int u, int v) {
        if (pos[u] > pos[v]) std::swap(u, v);
        return seq->qry(pos[u], pos[v]).second;
    }
};