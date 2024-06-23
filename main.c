#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"alg_sort.h"

int main()
{
    int nums[] = {11, 11, 11, 14};

    alg_insert_sort(nums, 4, int_compare_small_first);

    return 0;
}