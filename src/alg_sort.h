#ifndef __ALG_SORT_H
#define __ALG_SORT_H

/* 返回负数时，a排前面，返回正数时，b排前面 */
typedef int (*compare_func)(const void *a, const void *b);
int int_compare_small_first(const void *a, const void *b);
int int_compare_big_first(const void *a, const void *b);

/**
 * 不具备稳定性的排序：选择排序、快速排序、堆排序
 * 具备稳定性的排序：冒泡排序、插入排序、归并排序、桶排序
 */
void alg_bubble_sort(int *data, int size, compare_func cmp);

void alg_insert_sort(int *data, int size, compare_func cmp);

void alg_merge_sort(int *data, int start, int end, compare_func cmp);

void alg_quick_sort(int *data, int start, int end, compare_func cmp);

void alg_heap_adjust(int *data, int start, int heap_butt, compare_func cmp);
void alg_heap_insert(int *data, int idx, compare_func cmp);
void alg_heap_sort(int *data, int size, compare_func cmp);

void alg_radix_sort(unsigned int *data, unsigned int arry_size);

#endif