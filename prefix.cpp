//
// Created by Mac-2读者 on 2021/12/3.
//

#include <iostream>
#include <string.h>

using namespace std;
typedef long l;
l nxt[20000001] = {0};
l ct[20000001] = {0};
int len[20000001] = {0};
char s[20000001] = "";


int main() {
#ifndef _OJ_
    freopen("/Users/iMac-2/CLionProjects/PA_3/input.txt", "r", stdin);
#endif
    nxt[0] = -1;
    ct[0] = 1;
    len[0] = 1;
    scanf("%s", s);
    int length = 0;
    for (int i = 1; i < 20000001; ++i) {
        if (!(s[i]>='a' and s[i]<='z'))break;
        if (s[nxt[i - 1] + 1] == s[i]) {
            nxt[i] = nxt[i - 1] + 1;
            len[i] = len[nxt[i]] + 1;
            ct[i] = ct[i - 1] + len[i];
        } else if (s[i] == s[0]) {
            nxt[i] = 0;
            len[i] = 2;
            ct[i] = ct[i - 1] + len[i];
        } else {
            nxt[i] = nxt[i - 1];
            len[i] = 1;
            ct[i] = ct[i - 1] + len[i];
        }
        length ++;
    }
    cout << ct[length] << endl;

    return 0;
}