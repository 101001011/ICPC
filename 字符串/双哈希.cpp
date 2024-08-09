/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 查询子序列的双哈希值.
Time Complexity: O(n) - O(1).
Hash Value: 481f715f340ee766
Date: 2024/8/7
Open Source License: GPL
*/

template <typename type>
class Hash {
    static constexpr int b1 = 131, b2 = 1331;
    static constexpr int mod = 1e9 + 7;
    using u64 = unsigned long long;
private:
    int n;
    std::vector<type> s;
    std::vector<std::pair<int, u64>> ha, pw;

public:
    Hash(std::vector<type> s): s(s) {
        n = s.size();
        ha.resize(n), pw.resize(n);

        ha[0] = std::make_pair((int)s[0], (u64)s[0]);
        for (int i = 1; i < n; i++)
            ha[i].first = (1ll * ha[i - 1].first * b1 + s[i]) % mod,
            ha[i].second = ha[i - 1].second * b2 + s[i];
        
        pw[0].first = pw[0].second = 1;
        for (int i = 1; i < n; i++)
            pw[i].first = 1ll * pw[i - 1].first * b1 % mod,
            pw[i].second = pw[i - 1].second * b2;
    }

    std::pair<int, u64> code(int l, int r) {
        if (l == 0) return ha[r];
        return std::make_pair(
            (int)(ha[r].first - 1ll * ha[l - 1].first * pw[r - l + 1].first % mod + mod) % mod,
            ha[r].second - ha[l - 1].second * pw[r - l + 1].second
        );
    }
};