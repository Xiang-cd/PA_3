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
int buffer_size = 0;

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


void pbuff(int left_size) {
    debug("buffer:");
    for (int i = 0; i < left_size; ++i) {
        debug("%d ", buffer[i]);
    }
    debug("\n");
}

inline void select_number(int *cmp_var, int flag, int *begin, int *a, int *lens) {
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        if (i == flag)continue;
        cmp_var[index++] = a[begin[i]];
    }
}

inline void get_into_buffer(int *cmp_var, int min, int unselect_pos, int *begins, int *lens) {
    int i;
    for (i = 0; i < 3; ++i) if (min == cmp_var[i])break; //将最小元放入缓冲区
    buffer[buffer_size++] = cmp_var[i];
//    pbuff(buffer_size);
    if (i >= unselect_pos)i++; //确定是哪一路的子序列被放入
    if (lens[i]) {
        begins[i]++;
        lens[i]--;
    }
}

inline void change_flag(int *cmpvar, int max, int min, int &flag) {
    int i;
    for (i = 0; i < 3; ++i) if (max == cmpvar[i])break;
    if (i >= flag)i++;
    flag = i;
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
//    debug("%d %d %d %d %d\n", start, mid1, mid2, mid3, end);
    four_way_sort(start, mid1, a, n);
    four_way_sort(mid1, mid2, a, n);
    four_way_sort(mid2, mid3, a, n);
    four_way_sort(mid3, end, a, n);
    // 递归结束后进行归并
    buffer_size = 0;
    int unselect_pos = 3; //假设开始比较时不选择第四路
    int max, min;
    int cmp_var[3] = {0};
    int begins[4] = {start, mid1, mid2, mid3};
    int lens[4] = {mid1 - start, mid2 - mid1, mid3 - mid2, end - mid3};
    select_number(cmp_var, unselect_pos, begins, a, lens);
    compare(cmp_var[0], cmp_var[1], cmp_var[2], &max, &min);
    change_flag(cmp_var, max, min, unselect_pos);
    while (lens[0] and lens[1] and lens[2] and lens[3]) { //确保四路存在
//        debug("%d %d %d %d  %d\n", lens[0], lens[1], lens[2], lens[3], unselect_pos);
        select_number(cmp_var, unselect_pos, begins, a, lens);
        compare(cmp_var[0], cmp_var[1], cmp_var[2], &max, &min);
        get_into_buffer(cmp_var, min, unselect_pos, begins, lens);
        change_flag(cmp_var, max, min, unselect_pos);//根据最大值确定下一个不选择的路
    }
    int count = 0;
    for (int i = 0; i < 4; ++i) if (lens[i])count++;
    if (count == 3) {// 三路归并
        for (unselect_pos = 0; unselect_pos < 4; unselect_pos++)if (!lens[unselect_pos]) break;
        while (1) {
            int num = 0;
            for (int i = 0; i < 4; ++i) if (!lens[i])num++;
            if (num > 1)break;
//            debug("%d %d %d %d  %d\n", lens[0], lens[1], lens[2], lens[3], unselect_pos);
            select_number(cmp_var, unselect_pos, begins, a, lens);
            compare(cmp_var[0], cmp_var[1], cmp_var[2], &max, &min);
            get_into_buffer(cmp_var, min, unselect_pos, begins, lens);
        }
    }
    count = 0;
    for (int i = 0; i < 4; ++i) if (lens[i])count++;
    if (count == 2) { // 二路归并
        int rot[2];
        int index = 0;
        for (int i = 0; i < 4; ++i)if (lens[i])rot[index++] = i;
        while (lens[rot[0]] and lens[rot[1]]) {
//            debug("%d %d %d %d  %d\n", lens[0], lens[1], lens[2], lens[3], unselect_pos);
            if (compare(a[begins[rot[0]]], a[begins[rot[1]]])) {
                buffer[buffer_size++] = a[begins[rot[0]]++];
                lens[rot[0]]--;
            } else {
                buffer[buffer_size++] = a[begins[rot[1]]++];
                lens[rot[1]]--;
            }
        }
    }

    count = 0;
    for (int i = 0; i < 4; ++i) if (lens[i])count++;
    if (count <= 1) { //
//        debug("%d %d %d %d  %d\n", lens[0], lens[1], lens[2], lens[3], unselect_pos);
        int posi;
        for (posi = 0; posi < 4; posi++) if (lens[posi])break;
//        debug("%d \n",posi);
        if (posi != 4) {
            for (int i = 0; i < lens[posi]; ++i) {
                buffer[buffer_size++] = a[begins[posi]++];
            }
        }
//        pbuff(buffer_size);
    }

    if (buffer_size != end - start)exit(122);
    memcpy(a + start, buffer, sizeof(int) * buffer_size);
}


void sort(int n, int limit, int *a) {
    four_way_sort(0, n, a, n);
}