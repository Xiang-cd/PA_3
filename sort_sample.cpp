#include "sort.h"
#include <string.h>
#include <iostream>

using namespace std;
int Total = 0;

#define debug(...) fprintf(stderr, __VA_ARGS__)

int left_buffer[1000010] = {};
int mid_buffer[1000010] = {};
int right_buffer[1000010] = {};

bool compare(int x, int y) {
    int max, min;
    compare(x, y, y, &max, &min);
    return max == y;
}

int compare(int low, int mid, int upper) {
    Total++;
    int max, min;
    compare(low, mid, upper, &max, &min);
    if (max == mid)return 3;
    if (mid == min) return 1;
    return 2;
}

inline void swap(int &a, int &b) {
    int t = a;
    a = b, b = t;
}

void pbuff(int left_size, int mid_size, int right_size, int n, int *a, int start, int end) {
    printf("%d %d \n", start, end);
    cout << "left:";
    for (int i = 0; i < left_size; ++i) {
        printf("%d ", left_buffer[i]);
    }
    cout << endl;
    cout << "mid:";
    for (int i = 0; i < mid_size; ++i) {
        printf("%d ", mid_buffer[i]);
    }
    cout << endl;
    cout << "right:";
    for (int i = 0; i < right_size; ++i) {
        printf("%d ", right_buffer[i]);
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    cout << endl;
}


inline void three(int start, int end, int *a, int n) {
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

    int mid1 = a[start + rand() % (end - start)];
    int mid2 = a[start + rand() % (end - start)];
    while (mid1 == mid2) {
        mid2 = a[start + rand() % (end - start)];
    }
    int mid_size = 0;
    int left_size = 0;
    int right_size = 0;
    if (compare(mid2, mid1)) swap(mid1, mid2);
//    debug("mid1 %d mid2 %d\n", mid1, mid2);
    for (int i = start; i < end; ++i) {
        if (a[i] == mid1 or a[i] == mid2) continue;
        switch (compare(mid1, a[i], mid2)) {
            case 1:// 因该放在数组的最左边
                left_buffer[left_size++] = a[i];
                break;
            case 2:
                mid_buffer[mid_size++] = a[i];
                break;
            case 3:
                right_buffer[right_size++] = a[i];
                break;
        }
    }

    int soi = sizeof(int);
    int *start_address = a + start;
    memcpy(start_address, left_buffer, soi * left_size);
    a[start + left_size] = mid1;
    memcpy(start_address + (left_size + 1), mid_buffer, soi * mid_size);
    a[start + left_size + 1 + mid_size] = mid2;
    memcpy(start_address + (left_size + mid_size + 2), right_buffer, soi * right_size);

    three(start, start + left_size, a, n);
    three(start + left_size + 1, start + left_size + mid_size + 1, a, n);
    three(start + left_size + mid_size + 2, end, a, n);
}


void sort(int n, int limit, int *a) {
    three(0, n, a, n);
    if (Total > limit) exit(123);
//    for (int i = 0; i < n; ++i) {
//        printf("%d ", a[i]);
//    }
//    cout << endl;
}
