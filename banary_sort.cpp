//
// Created by 项小羽 on 2021/12/9.
//

#include "sort.h"
#include <string.h>
#include <iostream>
using namespace std;
int Total = 0;
#define debug(...) fprintf(stderr, __VA_ARGS__)

int lbuffer[1000010] = {};
int rbuffer[1000010] = {};

bool compare(int x, int y) {
    int max, min;
    compare(x, y, y, &max, &min);
    return max == y;
}

int compare(int a, int mid, int b) {
    Total++;
    int max, min;
    compare(a, mid, b, &max, &min);
    if (max == mid)return 1;
    if (min == mid) return 2;
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
    cout << "left:";
    for (int i = 0; i < left_size; ++i) {
        printf("%d ", lbuffer[i]);
    }
    cout << endl;
    cout << "right:";
    for (int i = 0; i < right_size; ++i) {
        printf("%d ", rbuffer[i]);
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    cout << endl;
}


inline void cmp(int first, int mid, int second, int &left_size, int &right_size) {
    switch (compare(first, mid, second)) {
        case 1:
            lbuffer[left_size++] = first;
            lbuffer[left_size++] = second;
            break;
        case 2:
            rbuffer[right_size++] = first;
            rbuffer[right_size++] = second;
            break;
        case 3:
            lbuffer[left_size++] = second;
            rbuffer[right_size++] = first;
            break;
        case 4:
            lbuffer[left_size++] = first;
            rbuffer[right_size++] = second;
            break;
    }
}

inline void binary_sort(int start, int end, int *a, int n) {
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
    int mid = a[start + rand() % (end - start)];
    int left_size = 0;
    int right_size = 0;
    for (int i = start; i < end; ++i) {
        if (a[i] == mid)continue;
        if (i < end - 2) {
            int first = a[i];
            int second = a[i + 1];
            if (second == mid) {
                second = a[i + 2];
                i++;
            }
            cmp(first, mid, second, left_size, right_size);
            i++;
        } else if (i == end - 2) {
            if (mid == a[end - 1]) {
                if (compare(mid, a[i])) rbuffer[right_size++] = a[i]; else lbuffer[left_size++] = a[i];
            } else {
                cmp(a[i], mid, a[i + 1], left_size, right_size);
                i++;
            }
        } else if (i == end - 1) {
            if (compare(mid, a[i]))rbuffer[right_size++] = a[i];
            else lbuffer[left_size++] = a[i];
        }
    }
    if (left_size + right_size + 1 != end - start){
        pbuff(left_size, right_size, n, a, start, end, mid);
        exit(12);
    }
    int soi = sizeof(int);
    int *start_address = a + start;
    memcpy(start_address, lbuffer, left_size * soi);
    a[start + left_size] = mid;
    memcpy(start_address + left_size + 1, rbuffer, right_size * soi);

//    pbuff(left_size, right_size, n, a, start, end, mid);

    binary_sort(start, start + left_size, a, n);
    binary_sort(start + left_size + 1, end, a, n);

}


void sort(int n, int limit, int *a) {
    binary_sort(0, n, a, n);
    if (Total > limit) exit(123);
    //    for (int i = 0; i < n; ++i) {
    //        printf("%d ", a[i]);
    //    }
    //    cout << endl;
}
