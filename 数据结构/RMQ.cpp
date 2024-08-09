/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 求静态区间并, 构造时需传入将两个元素并起来的函数, 如 `[](int x, int y) { return std::max(x, y); }`.
Time Complexity: O(n) - O(1).
Hash Value: fed0bf419e1bd10a
Date: 2024/7/29
Open Source License: GPL
*/

template <typename type>
class RMQ {
private:
    static constexpr unsigned w = 64;
    using u64 = unsigned long long;
    int n, m;
    std::function<type(type, type)> merge;
    std::vector<type> a, pre, suf;
    std::vector<u64> S;
    SparseTable<type> *ST;  // 定义见稀疏表.

public:
    RMQ(std::vector<type> a, std::function<type(type, type)> merge): merge(merge), a(a) {
        while (a.size() % w != 0) a.push_back(type());
        n = a.size(), m = (n + 1) / w;

        std::vector<type> arr(m);
        for (size_t i = 0; i < m; i++) {
            arr[i] = a[i * w];
            for (size_t j = 1; j < w; j++)
                arr[i] = merge(arr[i], a[i * w + j]);
        }
        ST = new SparseTable<type>(arr, merge);

        pre.resize(n), suf.resize(n);
        for (size_t i = 0; i < m; i++) {
            pre[i * w] = a[i * w];
            for (size_t j = 1; j < w; j++)
                pre[i * w + j] = merge(pre[i * w + j - 1], a[i * w + j]);
            suf[(i + 1) * w - 1] = a[(i + 1) * w - 1];
            for (int j = w - 2; j >= 0; j--)
                suf[i * w + j] = merge(suf[i * w + j + 1], a[i * w + j]);
        }

        S.resize(n);
        for (size_t i = 0; i < m; i++) {
            std::stack<size_t> sta;
            u64 st = 0;
            for (size_t j = 0; j < w; j++) {
                while (not sta.empty() and merge(a[i * w + sta.top()], a[i * w + j]) == a[i * w + j])
                    st ^= (1ull << sta.top()), sta.pop();
                st ^= (1ull << j), sta.push(j);
                S[i * w + j] = st;
            }
        }
    }

    type qry(int l, int r) {
        int idl = l / w, idr = r / w;
        if (idl != idr) {
            type ans = suf[l];
            if (idr - idl >= 2)
                ans = merge(ans, (*ST).qry(idl + 1, idr - 1));
            ans = merge(ans, pre[r]);
            return ans;
        } else {
            u64 st = S[r] >> (l - idl * w);
            int pos = __builtin_ffsll(st) - 1;
            return a[l + pos];
        }
    }
};