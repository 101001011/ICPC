/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 求一段代码去除注释和空白字符后的哈希值.
Time Complexity: O(code.size())
Hash Value: 656bc6114c74d40a
Date: 2024/6/12
Open Source License: GPL
*/

#include <bits/stdc++.h>

std::string format (const std::string& code) {
    std::string std;
    bool inBlock = false, inLine = false;
    for (size_t i = 0; i < code.size(); i++) {
        if (not inBlock and not inLine) {
            if (code[i] == '/' and i + 1 < code.size() and code[i + 1] == '*') inBlock = true, i++;
            else if (code[i] == '/' and i + 1 < code.size() and code[i + 1] == '/') inLine = true, i++;
            else if (not std::isspace(static_cast<unsigned char>(code[i]))) std += code[i];
        } else if (inBlock) {
            if (code[i] == '*' && i + 1 < code.size() && code[i + 1] == '/') inBlock = false, i++;
        } else if (inLine) {
            if (code[i] == '\n') inLine = false;
        }
    }
    return std;
}

unsigned long long hash (const std::string& code) {
    unsigned long long hash = 0;
    for (char c : code) hash = hash * 331 + c;
    return hash;
}

int main () {
    std::string code, line;
    while (std::getline(std::cin, line)) code += line + '\n';
    std::cout << "Hash Value: " << std::hex << hash(format(code)) << std::endl;
    system("pause");
    return 0;
}