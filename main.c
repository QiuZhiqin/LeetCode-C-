#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"alg_sort.h"

int main()
{
    int nums[] = {11, 143, 15, 106, 12, 13, 14};

    alg_heap_sort(nums, 7, int_compare_big_first);

    return 0;
}