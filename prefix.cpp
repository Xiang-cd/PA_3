//
// Created by Mac-2读者 on 2021/12/3.
//

#include <iostream>
#include <string.h>

using namespace std;
typedef int l;
l nxt[20000001] = {-1};
//l ct[20000001] = {0};
int len[20000001] = {0};
char s[20000001] = "";


int main() {
#ifndef _OJ_
//    freopen("/Users/iMac-2/CLionProjects/PA_3/output.txt", "r", stdin);
    freopen("/Users/xxy/CLionProjects/DSA/PA_3/input.txt", "r", stdin);
#endif
    nxt[0] = -1;
    len[0] = 1;
    scanf("%s", s);
    long long ans = 1;
    for (int i = 1; i < 20000001; ++i) {
        if (!(s[i] >= 'a' and s[i] <= 'z'))break;
        if (s[nxt[i - 1] + 1] == s[i]) {
            nxt[i] = nxt[i - 1] + 1;
            len[i] = len[nxt[i]] + 1;
        } else {
            l j = nxt[i - 1];
            while (j != -1) {
                if (s[j + 1] == s[i]) {
                    nxt[i] = j + 1;
                    len[i] = len[nxt[i]] + 1;
                    break;
                }
                j = nxt[j];
            }
            if (j == -1) {
                if (s[i] == s[0]) {
                    nxt[i] = 0;
                    len[i] = 2;
                } else {
                    len[i] = 1;
                    nxt[i] = -1;
                }
            }
        }
//        printf("i%d, %d %d  %lld\n", i, nxt[i], len[i], ans);
        ans += (long long) len[i];
    }
    cout << ans << endl;

    return 0;
}