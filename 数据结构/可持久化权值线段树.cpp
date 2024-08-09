/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 可持久化权值线段树, 支持查询数列的区间第 k 小.
Time Complexity: O(n \log n) - O(\log n).
Hash Value: f0a27d42755b3848
Date: 2024/7/30
Open Source License: GPL
*/

class PersistentVT {
private:
    int n, w, cnt;
    std::vector<int> val, rt, num, lc, rc;

    template <typename type>
    std::vector<type> discretize (std::initializer_list<std::vector<type>*> lists) {
        std::vector<type> values;
        for (auto list : lists) values.insert(values.end(), list->begin(), list->end());
        std::sort(values.begin(), values.end());
        values.erase(std::unique(values.begin(), values.end()), values.end());
        for (auto list : lists) for (auto& x : *list)
            x = (type)(std::lower_bound(values.begin(), values.end(), x) - values.begin());
        return values;
    }

    void build(int &x, int y, int l, int r, int k) {
        x = ++cnt, num[x] = num[y] + 1, lc[x] = lc[y], rc[x] = rc[y];
        if (l == r) return;
        int mid = l + r >> 1;
        if (k <= mid) build(lc[x], lc[y], l, mid, k);
        else build(rc[x], rc[y], mid + 1, r, k);
    }

    int query(int x, int y, int l, int r, int k) {
        if (l == r) return val[l];
        int mid = l + r >> 1;
        int sum = num[lc[x]] - num[lc[y]];
        if (k <= sum) return query(lc[x], lc[y], l, mid, k);
        else return query(rc[x], rc[y], mid + 1, r, k - sum);
    }

public:
    PersistentVT(std::vector<int> a): cnt(0) {
        n = a.size(), rt.resize(n + 1);
        val = discretize({&a}), w = val.size();
        size_t maxNum = 2 * (n + 1) * (log2(w) + 1);
        num.resize(maxNum), lc.resize(maxNum), rc.resize(maxNum);
        for (size_t i = 1; i <= n; i++)
            build(rt[i], rt[i - 1], 0, w, a[i - 1]);
    }

    int qry(int l, int r, int k) {
        return query(rt[r], rt[l - 1], 0, w, k);
    }
};