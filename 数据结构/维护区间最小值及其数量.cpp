/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 支持区间修改, 区间查询最小值及其数量的动态开点线段树. 
Time Complexity: O(n \log n) - O(\log n).
Hash Value: 3384781009d90abf
Date: 2024/8/9
Open Source License: GPL
*/

class SegmentTree {
private:
    class Node {
    public:
        Node *lc, *rc;
        int min, cnt, lazy;
        Node (int l, int r) : lc(nullptr), rc(nullptr), min(0), cnt(r - l + 1), lazy(0) {}
    } *root = nullptr;
    int limL, limR;

    void pushdown (Node* p, int L, int R) {
        if (p->lazy == 0) return;
        int mid = L + R >> 1;
        if (p->lc == nullptr) p->lc = new Node(L, mid);
        p->lc->min += p->lazy, p->lc->lazy += p->lazy;
        if (p->rc == nullptr) p->rc = new Node(mid + 1, R);
        p->rc->min += p->lazy, p->rc->lazy += p->lazy;
        p->lazy = 0;
    }

    std::pair<int, int> merge (std::pair<int, int> a, std::pair<int, int> b) {
        int min = std::min(a.first, b.first), cnt = 0;
        if (a.first == min) cnt += a.second;
        if (b.first == min) cnt += b.second;
        return std::make_pair(min, cnt);
    }

    void upd (int l, int r, int k, Node *&p, int L, int R) {
        if (p == nullptr) p = new Node(L, R);
        if (l <= L and R <= r) { p->min += k, p->lazy += k; return; }
        pushdown(p, L, R);
        int mid = L + R >> 1;
        if (l <= mid) upd(l, r, k, p->lc, L, mid);
        if (r >= mid + 1) upd(l, r, k, p->rc, mid + 1, R);
        if (p->lc == nullptr and p->rc == nullptr) std::tie(p->min, p->cnt) = std::make_pair(0, R - L + 1);
        else if (p->lc == nullptr) std::tie(p->min, p->cnt) = std::make_pair(0, mid - L + 1 + p->rc->cnt * (p->rc->min == 0));
        else if (p->rc == nullptr) std::tie(p->min, p->cnt) = std::make_pair(0, R - mid + p->lc->cnt * (p->lc->min == 0));
        else std::tie(p->min, p->cnt) = merge(std::make_pair(p->lc->min, p->lc->cnt), std::make_pair(p->rc->min, p->rc->cnt));
    }

    std::pair<int, int> qry (int l, int r, Node* p, int L, int R) {
        if (p == nullptr) return std::make_pair(0, std::min(r, R) - std::max(l, L) + 1);
        if (l <= L and R <= r) return std::make_pair(p->min, p->cnt);
        pushdown(p, L, R);
        int mid = L + R >> 1;
        auto res = std::make_pair(INT_MAX, 0);
        if (l <= mid) res = merge(res, qry(l, r, p->lc, L, mid));
        if (r >= mid + 1) res = merge(res, qry(l, r, p->rc, mid + 1, R));
        return res;
    }

    void del (Node* u) {
        if (u->lc != nullptr) del(u->lc);
        if (u->rc != nullptr) del(u->rc);
        delete u;
        u = nullptr;
    }

public:
    SegmentTree (int l, int r) : limL(l), limR(r), root(nullptr) {}

    void upd (int l, int r, int k) {
        upd(l, r, k, root, limL, limR);
    }

    std::pair<int, int> qry (int l, int r) {
        return qry(l, r, root, limL, limR);
    }

    ~SegmentTree () { del(root); }
};