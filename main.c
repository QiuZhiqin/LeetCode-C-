#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "alg_sort.h"
#include "myhash.h"

extern int longest_consecutive(int* nums, int numsSize);

int main(void)
{
    int nums[] = {1, 0, 1, 2};
    int result = 0;

    result = longest_consecutive(nums, sizeof(nums) / sizeof(int));
    printf("longest_consecutive: %d\n", result);
    printf("done\n");

    return 0;
}