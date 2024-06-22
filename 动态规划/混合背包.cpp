/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 求解多重背包问题. w, v, s 分别表示重量, 价值和数量.
Time Complexity: O(nm)
Hash Value: e362ccc48a2fcc26
Date: 2024/6/12
Open Source License: GPL
*/

int knapsack (std::vector<int> w, std::vector<int> v, std::vector<int> s, int m) {
    std::vector<int> f(m + 1), q(m + 1), r(m + 1);
    size_t n = w.size();
    for (size_t i = 0; i < n; i++) {
        if (w[i] * s[i] > m) {
            for (int j = w[i]; j <= m; j++)
                f[j] = std::max(f[j], f[j - w[i]] + v[i]);
        } else {
            s[i] = std::min(s[i], m / w[i]);
            for (int j = 0; j < w[i]; j++) {
                int h = 1, t = 0;
                for (int k = 0; k * w[i] + j <= m; k++) {
                    while (h <= t && k - r[h] > s[i]) h++;
                    while (h <= t && f[k * w[i] + j] - k * v[i] >= q[t]) t--; 
                    q[++t] = f[k * w[i] + j] - k * v[i], r[t] = k;
                    f[k * w[i] + j] = std::max(f[k * w[i] + j], q[h] + k * v[i]);
                }
            }	
        } 
    }
    return f[m];
}