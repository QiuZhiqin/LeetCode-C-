#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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