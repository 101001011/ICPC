/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 给定长度为 n 的序列, 求出它每个前缀的极长相同前后缀.
Time Complexity: O(n)
Hash Value: 73c07f35ce056ed2
Date: 2024/6/23
Open Source License: GPL
*/

template <typename type>
std::vector<int> border (const std::vector<type> &s) {
    size_t n = s.size();
    std::vector<int> pi(n);
    for (size_t i = 1, p = 0; i < n; p = pi[i], i++) {
        while (p and s[i] != s[p]) p = pi[p - 1];
        s[i] == s[p] ? pi[i] = p + 1 : p;
    }
    return pi;
}