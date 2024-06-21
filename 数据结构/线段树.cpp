/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 动态开点线段树框架.
Time Complexity: O(\log n) 单次修改与查询
Hash Value: 38b80179cacf3b24
Date: 2024/6/12
Open Source License: GPL
*/

class SegmentTree {
private:
    class Node {
    public:
        Node *lc, *rc;
        // 定义需要维护的变量
        Node (int l, int r) : lc(nullptr), rc(nullptr) /*初始化需要维护的变量*/ {}
    } *root = nullptr;
    int limL, limR;

    void pushdown (Node *p, int L, int R) {
        // if (p->lazy == 0) return;
        int mid = L + R >> 1;
        if (p->lc == nullptr) p->lc = new Node(L, mid);
        // 下传左子树
        if (p->rc == nullptr) p->rc = new Node(mid + 1, R);
        // 下传右子树
        // p->lazy = 0;
    }

    void pushup (Node *p, int L, int R) {
        int mid = L + R >> 1;
        if (p->lc == nullptr) p->lc = new Node(L, mid);
        if (p->rc == nullptr) p->rc = new Node(mid + 1, R);
        // 子树信息合并得到结点 p 的信息
    }

    void upd (int l, int r,/*需要做修改的参数*/ Node *&p, int L, int R) {
        if (p == nullptr) p = new Node(L, R);
        if (l <= L and R <= r) { /*对合法区间做修改*/ return; }
        pushdown(p, L, R);
        int mid = L + R >> 1;
        if (l <= mid) upd(l, r,/*需要做修改的参数*/ p->lc, L, mid);
        if (r >= mid + 1) upd(l, r,/*需要做修改的参数*/ p->rc, mid + 1, R);
        pushup(p, L, R);
    }

    /*需要查询的值类型*/ qry (int l, int r, Node* p, int L, int R) {
        if (p == nullptr) return /*空结点的信息*/;
        if (l <= L and R <= r) return /*结点 p 的信息*/;
        pushdown(p, L, R);
        int mid = L + R >> 1;
        auto res = /*需要查询的值类型的默认值*/;
        if (l <= mid) res = /*res 与左子树查询到的信息合并*/;
        if (r >= mid + 1) res = /*res 与右子树查询到的信息合并*/;
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

    // 提供给外界调用的接口

    ~SegmentTree () { del(root); }
};