#include "sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#define debug(...) fprintf(stderr, __VA_ARGS__)
// #define debug(...) 

template<class T>
inline void swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
}

static int n;
static int limit;

static int *A;
static int cmp_cnt = 0;

void compare(int a, int b, int c, int *max, int *min) {
    if (++cmp_cnt > limit) {
        printf("Wrong Answer --- exceeded limit\n");
        exit(0);
    }

    if (a < 0 || a >= n || b < 0 || b >= n || c < 0 || c >= n) {
        printf("Wrong Answer --- invalid parameters\n");
        exit(0);
    }

    if (A[a] > A[b]) swap(a, b);
    *max = A[b] > A[c] ? b : c;
    *min = A[a] < A[c] ? a : c;
}

int cmpfuncc(const void *a, const void *b) {
    return A[*(int *) a] - A[*(int *) b];
}

int main() {
    freopen("/Users/xxy/CLionProjects/DSA/PA_3/input.txt", "r", stdin);
    scanf("%d %d", &n, &limit);
    assert(n > 0);
    assert(limit > 0);

    A = new int[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    int *res = new int[n];
    int *res2 = new int[n];
    for (int i = 0; i < n; i++) {
        res2[i] = i;
        res[i] = i;
    }



    sort(n, limit, res);
    qsort(res2, n, sizeof(int), cmpfuncc);

//    for (int i = 0; i < n; ++i) {
//        printf("%d ",res[i]);
//    }
//    printf("\n");
//    for (int i = 0; i <n; ++i) {
//        printf("%d ",res2[i]);
//    }
//    printf("\n");

    for (int i = 0; i < n; i++) {
        if (res[i] < 0 || res[i] >= n) {
            printf("Wrong Answer --- res[%d] = %d not in [0, n)\n", i, res[i]);
            exit(0);
        }
        if (res[i] != res2[i]) {
            printf("Wrong Answer --- not sorted\n");
            exit(0);
        }
    }

    puts("Accepted");
    debug("cmp_cnt = %d\n", cmp_cnt);
}
