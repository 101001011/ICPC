/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 莫队算法求静态区间不同颜色数量.
Time Complexity: O(n \sqrt(m)).
Hash Value: d8125dae729df41e
Date: 2024/8/1
Open Source License: GPL
*/

class MoCaptainship {
private:
    class DifferentColors {
        friend class MoCaptainship;
        int m, num;
        std::vector<int> a, cnt;

        void add(int x) { num += not cnt[x]++; }
        void del(int x) { num -= not --cnt[x]; }

    public:
        DifferentColors(int m): m(m), num(0) {
            cnt.resize(m + 1);
        }
    };

    class Question {
        friend class MoCaptainship;
        int id, l, r, ans;
    public:
        Question(int id, int l, int r): id(id), l(l), r(r), ans(0) {}
    };

    int n, q;
    std::vector<int> a, bel;
    std::vector<Question> ask;

public:
    MoCaptainship(int n, std::vector<int> &a,
      std::vector<std::pair<int, int>> &seg): n(n), a(a) {
        q = seg.size(), bel.resize(n + 1);
        int B = sqrt(q), L = ceil(1.0 * n / B);
        for (size_t i = 1; i <= B; i++)
		    for (size_t j = (i - 1) * L + 1; j <= i * L; j++)
                if (j <= n) bel[j] = i;

        for (int i = 0; i < q; i++)
            ask.push_back(Question(i, seg[i].first, seg[i].second));
        std::sort(ask.begin(), ask.end(),
          [this](const Question &a, const Question &b) {
            return (bel[a.l] ^ bel[b.l]) ? bel[a.l] < bel[b.l] :
              ((bel[a.l] & 1) ? a.r < b.r : a.r > b.r);
        });

        DifferentColors diff(1000000);
        int l = 1, r = 0;
        for (auto &qs : ask) {
            while (l < qs.l) diff.del(a[l++]);
            while (l > qs.l) diff.add(a[--l]);
            while (r < qs.r) diff.add(a[++r]);
            while (r > qs.r) diff.del(a[r--]);
            qs.ans = diff.num;
        }

        std::sort(ask.begin(), ask.end(),
          [this](const Question &a, const Question &b) {
            return a.id < b.id;
        });
    }

    int ans(int id) { return ask[id].ans; }
};