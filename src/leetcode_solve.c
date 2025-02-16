#include "stdlib.h"
#include "myhash.h"
#include "alg_sort.h"

/* solution for leetcode problem: https://leetcode.cn/problems/longest-consecutive-sequence/description/ */
hash_table_stru *hash_table = NULL;

int longestConsecutive(int* nums, int numsSize) {
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

/* solution for solution for leetcode problem: https://leetcode.cn/problems/container-with-most-water/description/ */
int maxArea(int* height, int heightSize) {
    int left = 0, right = heightSize - 1;
    int max_area = 0;

    while (left < right) {
        int area = (right - left) * (height[left] < height[right] ? height[left] : height[right]);
        if (area > max_area) {
            max_area = area;
        }

        /* If left height is smaller than right height, move left pointer. Proof of this concusion is as follows:
         * Let's say the left height is x, and the right height is y, and x < y, t = right - left.
         * area = min(x, y) * t = x * t. If we move the right pointer, the new area will be min(x, y1) * (t - 1).
         * If y1 > y, then min(x, y1) * (t - 1) = x * (t - 1) < x * t.
         * If y1 < y, then min(x, y1) * (t - 1) <= min(x, y) * (t - 1) < x * t.
         * So, the new area will always be smaller than the old area if we move the right pointer, so we should move the left pointer.
         */
        if (height[left] <= height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return max_area;
}