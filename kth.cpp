#include "kth.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>

#define Len 500010
#define NN cout<<endl;
#define Debug false
#define Parent(x) ((x)-1)/2
#define Ls(x) (x)*2+1
#define Rs(x) (x)*2+2
int GN;
using namespace std;
typedef long l;

struct Pair {
    int x, y, z;

    Pair() : x(0), y(0), z(0) {};

    Pair(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

int aa[Len] = {0};
int bb[Len] = {0};
int cc[Len] = {0};
Pair heap[4 * Len] = {};
int hsize = 0;


int cmp(int index1, int index2) {
    if (Debug)printf("%d %d cmp\n", index1, index2);
    if (aa[heap[index1].x] < 1 || aa[heap[index1].x] > GN || bb[heap[index1].y] < 1 || bb[heap[index1].y] > GN ||
        cc[heap[index1].z] < 1 || cc[heap[index1].z] > GN)
        exit(123);
    if (aa[heap[index2].x] < 1 || aa[heap[index2].x] > GN || bb[heap[index2].y] < 1 || bb[heap[index2].y] > GN ||
        cc[heap[index2].z] < 1 || cc[heap[index2].z] > GN)
        exit(123);
    return compare(aa[heap[index1].x], bb[heap[index1].y], cc[heap[index1].z], aa[heap[index2].x], bb[heap[index2].y],
                   cc[heap[index2].z]);
}

void swp(int index1, int index2) {
    Pair tmp = Pair();
    memcpy(&tmp, &heap[index1], sizeof(Pair));
    memcpy(&heap[index1], &heap[index2], sizeof(Pair));
    memcpy(&heap[index2], &tmp, sizeof(Pair));
}


void push(int x, int y, int z) {
    if (Debug)printf("push %d %d %d \n", x, y, z);
    heap[hsize].x = x;
    heap[hsize].y = y;
    heap[hsize].z = z;
    int index = hsize;
    while (index > 0 and cmp(index, Parent(index))) {
        swp(index, Parent(index));
        index = Parent(index);
    }
    hsize++;
}


Pair pop() {
    Pair a = heap[0];
    memcpy(&heap[0], &heap[hsize - 1], sizeof(Pair));
    int index = 0;
    hsize--;
    while (1) {
        if (Ls(index) < hsize and Rs(index) < hsize) {
            if (cmp(Ls(index), Rs(index))) {
                if (cmp(Ls(index), index)) {
                    swp(index, Ls(index));
                    index = Ls(index);
                } else if (cmp(Rs(index), index)) {
                    swp(index, Rs(index));
                    index = Rs(index);
                } else break;
            } else {
                if (cmp(Rs(index), index)) {
                    swp(index, Rs(index));
                    index = Rs(index);
                } else if (cmp(Ls(index), index)) {
                    swp(index, Ls(index));
                    index = Ls(index);
                } else break;
            }
        } else if (Ls(index) < hsize) {
            if (cmp(Ls(index), index))swp(index, Ls(index));
            break;
        } else break;
    }
    return a;
}

int cmpfunca(const void *a, const void *b) {
    return compare(*(int *) b, 1, 1, *(int *) a, 1, 1);
}

int cmpfuncb(const void *a, const void *b) {
    return compare(1, *(int *) b, 1, 1, *(int *) a, 1);
}

int cmpfuncc(const void *a, const void *b) {
    return compare(1, 1, *(int *) b, 1, 1, *(int *) a);
}

void init(int n) {
    for (int i = 0; i <= n; ++i) {
        aa[i] = i;
        bb[i] = i;
        cc[i] = i;
    }
    qsort(aa + 1, n, sizeof(int), cmpfunca);
    qsort(bb + 1, n, sizeof(int), cmpfuncb);
    qsort(cc + 1, n, sizeof(int), cmpfuncc);
}


void get_kth(int n, int k, int *x, int *y, int *z) {
    init(n);
    if (Debug) {
        for (int i = 0; i <= n; ++i)printf("%d ", aa[i]);
        NN
        for (int i = 0; i <= n; ++i)printf("%d ", bb[i]);
        NN
        for (int i = 0; i <= n; ++i)printf("%d ", cc[i]);
        NN
    }
    GN = n;
    push(1, 1, 1);
    Pair tmp = Pair();
    while (k) {
        tmp = pop();
        if (Debug)printf("pop %d %d %d   %d %d %d \n", tmp.x, tmp.y, tmp.z, aa[tmp.x], bb[tmp.y], cc[tmp.z]);
        if (tmp.z + 1 <= n)push(tmp.x, tmp.y, tmp.z + 1);
        if (tmp.z == 1) {
            if (tmp.x + 1 <= n)push(tmp.x + 1, tmp.y, tmp.z);
            if (tmp.y + 1 <= n and tmp.x == 1) { push(tmp.x, tmp.y + 1, tmp.z); }
        }
        if (Debug) {
            for (int i = 0; i < hsize; ++i) {
                printf("i%d, %d %d %d\n", i, heap[i].x, heap[i].y, heap[i].z);
            }
        }
        k--;
    }
    *x = aa[tmp.x];
    *y = bb[tmp.y];
    *z = cc[tmp.z];
}
