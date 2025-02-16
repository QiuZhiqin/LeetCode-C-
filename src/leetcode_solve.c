#include "stdlib.h"
#include "myhash.h"
#include "alg_sort.h"

hash_table_stru *hash_table = NULL;

int longest_consecutive(int* nums, int numsSize) {
    int longest_consecutive = 0;
    int cur_num, cur_len;

    for (size_t i = 0; i < numsSize; i++) {
        hash_add_item(&hash_table, nums[i]);
    }

    qsort(nums, numsSize, sizeof(int), int_compare_small_first);
    for (size_t i = 0; i < numsSize; i++) {
        if (hash_find_item(hash_table, nums[i] - 1)) {
            continue;
        }

        cur_len = 1;
        cur_num = nums[i] + 1;
        while(hash_find_item(hash_table, cur_num)) {
            cur_len++;
            cur_num++;
        }

        if (cur_len > longest_consecutive) {
            longest_consecutive = cur_len;
        }
    }

    return longest_consecutive;
}