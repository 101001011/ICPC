/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 求出序列的其中一个最长不下降(上升)子序列.
Time Complexity: O(n \log n)
Date: 2024/6/12
Open Source License: GPL
*/

template <typename type>
std::vector<type> lis_non_strictly (const std::vector<type> &a) {
    size_t n = a.size();
    std::vector<type> sta(1, a[0]);
    for (size_t i = 1; i < n; i++) {
        if (a[i] >= sta.back()) sta.push_back(a[i]);
        else sta[std::upper_bound(sta.begin() , sta.end() , a[i]) - sta.begin()] = a[i];
    }
    return sta;
}
// Hash Value: dddcd9b14c4e2cb0

template <typename type>
std::vector<type> lis_strictly (const std::vector<type> &a) {
    size_t n = a.size();
    std::vector<type> sta(1, a[0]);
    for (size_t i = 1; i < n; i++) {
        if (a[i] > sta.back()) sta.push_back(a[i]);
        else sta[std::lower_bound(sta.begin() , sta.end() , a[i]) - sta.begin()] = a[i];
    }
    return sta;
}
// Hash Value: 351502e61080b3f2