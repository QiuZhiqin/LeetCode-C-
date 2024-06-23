#ifndef __ALG_SORT_H
#define __ALG_SORT_H

/* 返回负数时，a排前面，返回正数时，b排前面 */
typedef int (*compare_func)(void *a, void *b);
int int_compare_small_first(void *a, void *b);
int int_compare_big_first(void *a, void *b);

void alg_merge_sort(int *data, int start, int end, compare_func cmp);

void alg_quick_sort(int *data, int start, int end, compare_func cmp);

void alg_heap_sort(int *data, int size, compare_func cmp);

void alg_radix_sort(unsigned int *data, unsigned int arry_size);

#endif