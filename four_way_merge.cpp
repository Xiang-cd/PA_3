//
// Created by 项小羽 on 2021/12/10.
//

#include "sort.h"
#include <string.h>
#include <iostream>

using namespace std;
int Total = 0;
#define debug(...) fprintf(stderr, __VA_ARGS__)

int buffer[1000010] = {};

bool compare(int x, int y) {
    int max, min;
    compare(x, y, y, &max, &min);
    return max == y;
}

int compare(int a, int b, int c) {
    Total++;
    int max, min;
    compare(a, b, c, &max, &min);
    if (max == a) return 3;
    if (max == b) return 4;
    exit(110);
}

inline void swap(int &a, int &b) {
    int t = a;
    a = b, b = t;
}


void pbuff(int left_size, int right_size, int n, int *a, int start, int end, int mid) {
    printf("%d %d  %d\n", start, end, mid);
    cout << "buffer:";
    for (int i = 0; i < left_size; ++i) {
        printf("%d ", buffer[i]);
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    cout << endl;
}

inline void select_number(int *cmp_var, int flag, int *begin, int *a) {
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        if (i == flag)continue;
        cmp_var[index++] = a[begin[i]];
    }
}


void four_way_sort(int start, int end, int *a, int n) {
    // 递归基
    if (end - start <= 3) {
        if (end - start <= 1)return;
        if (end - start == 2) {
            if (!compare(a[start], a[start + 1]))swap(a[start], a[start + 1]);
            return;
        } else {
            int max, min, mid = 0;
            compare(a[start], a[start + 1], a[start + 2], &max, &min);
            for (int i = 0; i < 3; ++i) {
                if (a[start + i] != max and a[start + i] != min) {
                    mid = a[start + i];
                    break;
                }
            }
            a[start] = min;
            a[start + 1] = mid;
            a[start + 2] = max;
            return;
        }
    }
    // 向下递归
    int mid1 = start + (end - start) / 4;
    int mid2 = start + (end - start) / 2;
    int mid3 = start + 3 * (end - start) / 4;
    four_way_sort(start, mid1, a, n);
    four_way_sort(mid1, mid2, a, n);
    four_way_sort(mid2, mid3, a, n);
    four_way_sort(mid3, end, a, n);
    // 递归结束后进行归并
    int unselect_pos = 3; //假设开始比较时不选择第四路
    int max, min;
    int cmp_var[3] = {0};
    int begins[4] = {start, mid1, mid2, mid3};
    int lens[4] = {mid1 - start, mid2 - mid1, mid3 - mid2, end - mid3};
    while (lens[0] > 0 or lens[1] > 0 or lens[2] > 0 or lens[3] > 0) {
        select_number(cmp_var, unselect_pos, begins, a);
        compare(cmp_var[0], cmp_var[1], cmp_var[2], &max, &min);


    }


}


void sort(int n, int limit, int *a) {
    four_way_sort(0, n, a, n);
}