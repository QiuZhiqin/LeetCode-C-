#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"alg_sort.h"

int main()
{
    int nums[] = {11, 143, 15, 106, 12, 13, 14};

    alg_radix_sort(nums, 7);

    return 0;
}