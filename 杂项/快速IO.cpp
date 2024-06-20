/*
Author: CCA
Contact Method: c-c-a@qq.com
Function: 快速输入输出. 使用格式为 read(a, b, c), print(a, 'EndCharacter'); 记得将 return 0; 改为 return flush(), 0; 
Time Complexity: O(InputLen)
Hash Value: 8c8a8fc55f78c368
Date: 2024/6/12
Open Source License: GPL
*/

namespace IO {
const int BUF_SIZ = 1 << 20;
char obuf[BUF_SIZ], *oS = obuf, *oT = oS + BUF_SIZ;

#define flush() (fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void())
#define putchar(x) (*oS++ = (x), oS == oT ? flush() : void())

void _print (int u) { if(u > 9) _print(u / 10); putchar(u % 10 + 48); }
void print (int u, char End) { if (u < 0) putchar('-'), u = -u; _print(u), putchar(End); }

char ibuf[BUF_SIZ], *iS = ibuf, *iT = ibuf;
#define getchar() (iS == iT && (iT = (iS = ibuf) + fread(ibuf, 1, BUF_SIZ, stdin)), iS == iT ? EOF : *iS++)

template <typename _Tp>
void read (_Tp &x) {
    char ch(getchar()); bool sym(false);
    while (!isdigit(ch)) sym |= ch == 45, ch = getchar();
    x = ch & 15, ch = getchar();
    while (isdigit(ch)) x = x * 10 + (ch & 15), ch = getchar();
    if (sym) x = -x;
}
template <typename _Tp, typename... Args>
void read (_Tp &t, Args &...args) { read(t); read(args...); }
}