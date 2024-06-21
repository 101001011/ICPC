/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 以 {&a, &b, &c} 格式传入若干个数组, 将原数组离散化后返回存储了所有出现过恰好一次的元素的数组.
Time Complexity: O(\sum len \log \sum len)
Hash Value: 1a5a22897997aa1e
Date: 2024/6/12
Open Source License: GPL
*/

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