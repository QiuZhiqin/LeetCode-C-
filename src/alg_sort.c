#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"common.h"
#include"alg_sort.h"

int int_compare_small_first(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

int int_compare_big_first(const void *a, const void *b)
{
    return *(int*)b - *(int*)a;
}

void alg_bubble_sort(int *data, int size, compare_func cmp)
{
    bool flag;

    if (data == NULL || size == 0) {
        printf("alg_bubble_sort: invalid input");
        return;
    }

    if (cmp == NULL) {
        cmp = int_compare_small_first;
    }

    for (int i = 0; i < size; ++i) {
        flag = false;
        /* 从右边往左冒泡，每次找出一个最大/最小的数放在左边 */
        for (int j = size - 1; j > i; --j) {
            if (cmp(&data[j - 1], &data[j]) > 0) {
                swap(&data[j - 1], &data[j]);
                flag = true;
            }
        }

        /* 一次冒泡没有交换，认为数组已经有序 */
        if (flag == false) {
            return;
        }
    }
}

void alg_insert_sort(int *data, int size, compare_func cmp)
{
    int cur;

    if (data == NULL || size == 0) {
        printf("alg_insert_sort: invalid input");
        return;
    }

    if (cmp == NULL) {
        cmp = int_compare_small_first;
    }

    for (int i = 1; i < size; ++i) { // 从第二个数开始插入，因为仅有一个数的数组一定有序
        cur = data[i];
        int j;
        /* 从右往左遍历有序数组，找到cur应当插入的位置 */
        for (j = i - 1; j >= 0; --j) {
            if (cmp(&cur, &data[j]) >= 0) {
                break;
            }

            data[j + 1] = data[j];
        }

        data[j + 1] = cur;
    }
}

void alg_merge_sort(int *data, int start, int end, compare_func cmp)
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

    if (cmp == NULL) {
        cmp = int_compare_small_first;
    }

    // 计算中间点
    mid = start + ((end - start) >> 1);
    alg_merge_sort(data, start, mid, cmp);
    alg_merge_sort(data, mid + 1, end, cmp);

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
        help[idx++] = (cmp(&data[p1], &data[p2]) < 0) ? data[p1++] : data[p2++];
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

int alg_partition(int *data, int start, int end, compare_func cmp)
{
    int left, right, pivot;

    left = start;
    right = end - 1;
    pivot = data[end]; // 选择当前数组最后一个元素作支点

    while (left <= right) {
        if (cmp(&data[left], &pivot) <= 0) {
            left++;
        } else {
            swap(&data[left], &data[right]);
            right--;
        }
    }

    swap(&data[left], &data[end]);

    return left;
}

void alg_quick_sort(int *data, int start, int end, compare_func cmp)
{
    int pos;

    if (data == NULL || start < 0 || end < 0) {
        printf("alg_quick_sort: invalid input");
        return;
    }

    if (start >= end) {
        return;
    }

    if (cmp == NULL) {
        cmp = int_compare_small_first;
    }

    pos = alg_partition(data, start, end, cmp);

    alg_quick_sort(data, start, pos - 1, cmp);
    alg_quick_sort(data, pos + 1, end, cmp);
}

/*
O(logN)
大根堆的调整，通常在大根堆删除元素时使用，把放到start位置的新元素下沉到属于它的位置，让大根堆依然成立
*/
void alg_heap_adjust(int *data, int start, int heap_butt, compare_func cmp)
{
    if (data == NULL || start < 0 || heap_butt < 0) {
        printf("alg_heap_adjust: invalid input");
        return;
    }

    if (start > heap_butt) {
        return;
    }

    if (cmp == NULL) {
        cmp = int_compare_big_first; // 默认大根堆
    }

    for (int i = 2 * start + 1; i <= heap_butt; i = 2 * i + 1) {
        /* find the bigger/smaller child */
        if (i + 1 <= heap_butt && cmp(&data[i], &data[i + 1]) < 0) {
            i++;
        }

        if (cmp(&data[start], &data[i]) < 0) {
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
void alg_heap_insert(int *data, int idx, compare_func cmp)
{
    int father_idx;
    if (data == NULL || idx < 0) {
        printf("alg_heap_insert: invalid input");
    }

    if (cmp == NULL) {
        cmp = int_compare_big_first; // 默认大根堆
    }

    father_idx = (idx - 1) / 2;
    while (father_idx >= 0 && cmp(&data[father_idx], &data[idx]) < 0) {
        swap(&data[father_idx], &data[idx]);
        idx = father_idx;
        father_idx = (idx - 1) / 2;
    }
}

void alg_heap_sort(int *data, int size, compare_func cmp)
{
    if (data == NULL || size < 0) {
        printf("alg_heap_sort: invalid input");
    }

    for (int i = 0; i < size; ++i) {
        alg_heap_insert(data, i, cmp);
    }

    for (int heap_butt = size - 1; heap_butt > 0; ) {
        swap(&data[0], &data[heap_butt--]);
        alg_heap_adjust(data, 0, heap_butt, cmp);
    }
}

/* 仅可比较正整数 */
void alg_radix_sort(unsigned int *data, unsigned int arry_size)
{
    unsigned int maxbits = 0;
    unsigned int *bucket = NULL;
    int count[10] = { 0 };

    if (data == NULL || arry_size == 0) {
        return;
    }

    bucket = (unsigned int *)malloc(sizeof(unsigned int) * arry_size);
    if (bucket == NULL) {
        printf("malloc failed\n");
        return;
    }

    memset(bucket, 0, sizeof(unsigned int) * arry_size);
    maxbits = get_maxbits(data, arry_size);
    for (int i = 0; i < maxbits; ++i) {
        for (int j = 0; j < arry_size; ++j) {
            count[get_digit(data[j], i)]++; // 计算每个基数出现的次数
        }

        for (int j = 1; j < 10; ++j) {
            count[j] = count[j - 1] + count[j]; //计算基数小于等于自己的数的个数
        }

        /* 
        根据count数组找到自己的位置 此处从右向左遍历是为了保持相对顺序,例：data = {12, 11, 13, 15}
        经过第一次入桶出桶,得到的顺序是11 12 13 15。第二次入桶,得到count[1] == 4, 这时如果从左边开始遍历，出桶得到的结果就是15 13 12 11，显然与预期不符
        */
        for (int j = arry_size - 1; j >= 0; --j) {
            int digit = get_digit(data[j], i);
            bucket[count[digit] - 1] = data[j];
            count[digit]--;
        }

        for (int j = 0; j < arry_size; ++j) {
            data[j] = bucket[j];
        }

        /* 完成一次入桶出桶，count数组清空 */
        memset(count, 0, sizeof(unsigned int) * 10);
    }

    free(bucket);
}