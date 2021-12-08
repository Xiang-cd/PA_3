#include <iostream>
#include <stdlib.h>
#include <cstdio>

using namespace std;
#define Debug true
#define HasSingleChild(x) !((x)->l and (x)->r)

struct node {
    node() : l(NULL), r(NULL), p(NULL) {};
    node *l;
    node *r;
    node *p;
    ~node() {
        if (r)delete r;
        if (l)delete l;
    }
};

typedef unsigned long l;
char s[65] = "";
node *root;
int n, k;
l shape[500000] = {0};

l get_bit(l input, int posi) {
    return (input >> (63 - posi) & 1);
}


node *  insert(int posi) {
    node *work = root;
    for (int i = 0; i < 64; ++i) {
        if (s[i] - '0') {
            if (!work->r) {
                work->r = new node();
                work->r->p = work;
            }
            work = work->r;
        } else {
            if (!work->l) {
                work->l = new node();
                work->l->p = work;
            }
            work = work->l;
        }
    }
    // 如果相同的形态已经插入，则取先进入的为好
    return work;
}

// 注意到插入到时候是有输入的，但是删除的时候还是得从数组中取数

void remove(l target) {
    node *work = root;
    for (int i = 0; i < 64; ++i) {
        if (get_bit(target, i)) {
            if (!work->r) return;
            work = work->r;
        } else {
            if (!work->l) return;
            work = work->l;
        }
    }
    while (work->p) {
        if (HasSingleChild(work->p)) {
            work = work->p;
            if (work->r) delete work->r;
            if (work->l) delete work->l;
            work->r = NULL;
            work->l = NULL;
        } else {
            node *tmp = work;
            work = work->p;
            if (work->r == tmp)work->r = NULL;
            else work->l = NULL;
            delete tmp;
            return;
        }
    }
}

int match(l target) {
//匹配最大值，从高位开始尽量取位不同的值
    node *work = root;
    for (int i = 0; i < 64 and work; ++i) {
        if (get_bit(target, i)) {
            if (work->l) work = work->l;
            else work = work->r;
        } else {
            if (work->r)work = work->r;
            else work = work->l;
        }
    }
    if (work->posi)return work->posi;
    else return -1;
}


l tolong() {
    l ans = 0;
    for (int i = 0; i < 64; ++i) {
        ans = ans << 1;
        if (s[i] - '0')++ans;
    }
    return ans;
}


int main() {
#ifndef _OJ_
    freopen("/Users/iMac-2/CLionProjects/PA_3/input.txt", "r", stdin);
#endif
    cin >> n;
    cin >> k;
    root = new node();
    int start = 0;
    int end = -1;
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        if (end - start >= 2 * (k + 1)) {
            remove(shape[start]);
            start++;
        }
        shape[i] = tolong();
        insert(i);
        end++;
        if (end - (k + 1) >= 0) {
            cout << match(shape[end - k - 1]) << endl;
        }
    }
    remove(shape[start]);
    start++;
    while (start + k + 1 < n) {
        cout << match(shape[start + k + 1]) << endl;
        remove(shape[start]);
        start++;
    }
    return 0;
}
