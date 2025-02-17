#include "stdlib.h"
#include "myhash.h"
#include "alg_sort.h"

/* solution leetcode problem: https://leetcode.cn/problems/longest-consecutive-sequence/description/ */
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

/* solution leetcode problem: https://leetcode.cn/problems/container-with-most-water/description/ */
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

/* solution leetcode problem: https://leetcode.cn/problems/3sum/description/ */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** ret_array = NULL;
    int i, j, k, tmp;

    /* Why choose size numsSize * numsSize? 
     * The numbers of combination is C(numSize, 2) instead of C(numSize, 3), beacuse when we determine the number one and two, the number three is also determined.
     * So the maximum size of the return array is (numsSize * (numsSize - 1)) / 2 < numsSize * numsSize.
     */
    ret_array = (int**)malloc(sizeof(int*) * numsSize * numsSize);
    if (ret_array == NULL) {
        printf("threeSum: malloc failed\n");
        return NULL;
    }

    *returnColumnSizes = (int*)malloc(sizeof(int) * numsSize * numsSize);
    *returnSize = 0;

    qsort(nums, numsSize, sizeof(int), int_compare_small_first);
    for ( i = 0; i < numsSize - 2; i++) {
        j = i + 1;
        k = numsSize - 1;
        tmp = nums[i];
        /* The cur number eaquals to the last number means the last number is already processed.*/
        if (i > 0 && tmp == nums[i - 1]) {
            continue;
        }

        /* If the sum of the smallest three numbers is bigger than 0, the sum of tmp and other numbers must bigger than 0 too.*/
        if (tmp + nums[i + 1] + nums[i + 2] > 0) {
            break;
        }

        while (j < k && j < numsSize && k > 0) {
            if (tmp + nums[j] + nums[k] == 0) {
               ret_array[*returnSize] = (int*)malloc(sizeof(int) * 3);
               if (ret_array[*returnSize] == NULL) {
                   printf("threeSum: malloc failed\n");
                   return NULL;
               }
               ret_array[*returnSize][0] = nums[i];
               ret_array[*returnSize][1] = nums[j];
               ret_array[*returnSize][2] = nums[k];
               (*returnColumnSizes)[*returnSize] = 3;
               (*returnSize)++;
               j++;
               k--;

               while (j < k && nums[j] == nums[j - 1]) {
                   j++;
               }

               while (j < k && nums[k] == nums[k + 1]) {
                   k--;
               }
           } else if (tmp + nums[j] + nums[k] < 0) {
               j++;
           } else {
               k--;
           }
       }
    }

    return ret_array;
}