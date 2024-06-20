/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 求不大于 x 的正整数中有多少个满足任意相邻两数位之差不小于 2.
Time Complexity: O(\log x)
Hash Value: 959e399c4c11df3d
Date: 2024/6/12
Open Source License: GPL
*/

std::vector<int> a;
std::vector<std::vector<int>> f;

int dfs (int pos, int pre, int lim, int led) {
    if (!pos) return led ^ 1;
    if (!lim && !led && f[pos][pre] != -1) return f[pos][pre]; 
    int up = lim ? a[pos] : 9, sum = 0;
    for (int p = 0; p <= up; p++) if (abs(pre - p) > 1 || led)
        sum += dfs(pos - 1, p, lim & (p == up), led & (!p));
    if (!lim && !led) f[pos][pre] = sum; 
    return sum;
}

int count (int x) {
    a.resize(1, 0);
    while (x) a.push_back(x % 10), x /= 10;
    f.resize(a.size(), std::vector<int>(10, -1));
    if (a.size() == 1) return 0;
    return dfs(a.size() - 1, 0, true, true);
}