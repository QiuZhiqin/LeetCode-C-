#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"common.h"

void alg_merge_sort(int *data, int start, int end)
{
    int mid, p1, p2, idx = 0;
    int *help = NULL;

    // 检查输入数据的有效性
    if (data == NULL || start > end) {
        printf("错误：输入数据有误\n");
        return;
    }

    // 递归结束条件
    if (start == end) {
        return;
    }

    // 计算中间点
    mid = start + ((end - start) >> 1);
    alg_merge_sort(data, start, mid);
    alg_merge_sort(data, mid + 1, end);

    // 分配临时数组空间
    help = (int *)malloc((end - start + 1) * sizeof(int));
    if (help == NULL) {
        printf("错误：内存分配失败\n");
        return;
    }

    // 归并过程
    p1 = start;
    p2 = mid + 1;
    while (p1 <= mid && p2 <= end) {
        help[idx++] = (data[p1] <= data[p2]) ? data[p1++] : data[p2++];
    }

    // 处理剩余元素
    while (p1 <= mid) {
        help[idx++] = data[p1++];
    }

    while (p2 <= end) {
        help[idx++] = data[p2++];
    }

    // 将排序结果拷贝回原数组
    for (int i = 0; i < idx; i++) {
        data[start + i] = help[i];
    }

    // 释放临时数组的内存
    free(help);

    return;
}

int alg_partition(int *data, int start, int end)
{
    int left, right, pivot;

    left = start;
    right = end - 1;
    pivot = data[end]; // 选择当前数组最后一个元素作支点

    while (left <= right) {
        if (data[left] <= pivot) {
            left++;
        } else {
            swap(&data[left], &data[right]);
            right--;
        }
    }

    swap(&data[left], &data[end]);

    return left;
}

void alg_quick_sort(int *data, int start, int end)
{
    int pos;

    if (data == NULL || start < 0 || end < 0) {
        printf("alg_quick_sort: invalid input");
        return;
    }

    if (start >= end) {
        return;
    }

    pos = alg_partition(data, start, end);

    alg_quick_sort(data, start, pos - 1);
    alg_quick_sort(data, pos + 1, end);
}

/*
O(logN)
大根堆的调整，通常在大根堆删除元素时使用，把放到start位置的新元素下沉到属于它的位置，让大根堆依然成立
*/
static void alg_heap_adjust(int *data, int start, int heap_butt)
{
    if (data == NULL || start < 0 || heap_butt < 0) {
        printf("alg_heap_adjust: invalid input");
        return;
    }

    if (start > heap_butt) {
        return;
    }

    for (int i = 2 * start + 1; i <= heap_butt; i = 2 * i + 1) {
        /* find the bigger child */
        if (i + 1 <= heap_butt && data[i] < data[i + 1]) {
            i++;
        }

        if (data[start] < data[i]) {
            swap(&data[start], &data[i]);
            start = i;
        } else {
            break;
        }
    }
}

/*
O(logN)
往大根堆里插入新元素，使新元素上浮到属于它的位置，让大根堆依然成立（使用前先把待插入值放到data[idx]）
*/
static void alg_heap_insert(int *data, int idx)
{
    int father_idx;
    if (data == NULL || idx < 0) {
        printf("alg_heap_insert: invalid input");
    }

    father_idx = (idx - 1) / 2;
    while (father_idx >= 0 && data[father_idx] < data[idx]) {
        swap(&data[father_idx], &data[idx]);
        idx = father_idx;
        father_idx = (idx - 1) / 2;
    }
}

void alg_heap_sort(int *data, int size)
{
    if (data == NULL || size < 0) {
        printf("alg_heap_sort: invalid input");
    }

    for (int i = 0; i < size; ++i) {
        alg_heap_insert(data, i);
    }

    for (int heap_butt = size - 1; heap_butt > 0; ) {
        swap(&data[0], &data[heap_butt--]);
        alg_heap_adjust(data, 0, heap_butt);
    }
}