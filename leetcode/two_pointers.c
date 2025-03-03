#include "stdlib.h"
#include "alg_sort.h"

/* Solution for leetcode problem: https://leetcode.cn/problems/container-with-most-water/description/ */
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

/* Solution for leetcode problem: https://leetcode.cn/problems/3sum/description/ */
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

/* Solution for leetcode problem: https://leetcode.cn/problems/trapping-rain-water/description/ */

/* Solution1: My Original Solution
 * For each height, we find the position where the height is smaller than the current height, i.e., height[pos] < cur_height.
 * Then we find the left and right bound of the water, i.e., the left and right position where the height is bigger than cur_height.
 * The volume of current heighr is right - left - 1. Perform this operation for each height, accumulate the volume.
 * The time complexity is O(n * h). n = heightSize, h = max(height[0], height[1], ..., height[heightSize - 1]).
 */
int trap1(int* height, int heightSize) {
    int left, right, volume = 0;

    if (heightSize < 3) {
        return 0;
    }

    for (int cur_height = 1; ; ++cur_height) {
        for (int i = 1; i < heightSize - 1 ; ++i) {
            if (height[i] < cur_height) {
                left =  i - 1;
                right = i + 1;
                /* Find the left bound */
                while (left >= 0 && height[left] < cur_height) {
                    left--;
                }
                /* Find the right bound */
                while (right < heightSize && height[right] < cur_height) {
                    right++;
                }

                if (left >= 0 && right < heightSize) {
                    volume += right - left - 1;
                    i = right;
                /* The left and right bound are not found, meaning the current height is the highest. */
                } else if (left < 0 && right >= heightSize) {
                    return volume;
                } else if (left < 0) { // The left bound is not found, meaning height[right] is the highest.
                    i = right;
                } else { // The right bound is not found, meaning height[left] is the highest, break the loop to next height.
                    break;
                }
            }
        }
    }

    return volume;
}

/* Solution2: Solution of a random guy on leetcode
 * We can find the highest height and its position, then we calculate the volume of the left and right part of the highest height.
 * The time complexity is O(n), the space complexity is O(1).
 */
int trap2(int* height, int heightSize) {
    int max_height = 0, max_height_pos, volume = 0, water_height = 0;

    for (int i = 0; i < heightSize; ++i) {
        if (height[i] > max_height) {
            max_height = height[i];
            max_height_pos = i;
        }
    }

    if (max_height_pos == -1)
        return 0;

    for (int i=0; i < max_height_pos; i++) {
        if (height[i] > water_height)
            water_height = height[i];
        volume += water_height - height[i];
    }
    water_height = 0;
    for (int i = heightSize - 1; i > max_height_pos; i--) {
        if (height[i] > water_height)
            water_height = height[i];
        volume += water_height - height[i];
    }

    return volume;
}

/* Solution3: Dynamic Programming
 * We use two arrays to store the left and right max height of each position.
 * The time complexity is O(n), the space complexity is O(n).
 */
int trap3(int* height, int heightSize) {
    int *left_max = NULL, *right_max = NULL;
    int volume = 0;

    left_max = (int *)malloc(sizeof(int) * heightSize);
    if (left_max == NULL) {
        printf("trap: malloc failed\n");
        return 0;
    }
    right_max = (int *)malloc(sizeof(int) * heightSize);
    if (right_max == NULL) {
        printf("trap: malloc failed\n");
        free(left_max);
        return 0;
    } 
    memset(left_max, 0, sizeof(int) * heightSize);
    memset(right_max, 0, sizeof(int) * heightSize);


    /* Initialize left_max array */
    left_max[0] = height[0];
    for (int i = 1; i < heightSize; i++) {
        left_max[i] = (height[i] > left_max[i - 1]) ? height[i] : left_max[i - 1];
    }

    /* Initialize right_max array */
    right_max[heightSize - 1] = height[heightSize - 1];
    for (int i = heightSize - 2; i >= 0; i--) {
        right_max[i] = (height[i] > right_max[i + 1]) ? height[i] : right_max[i + 1];
    }

    /* Volume of trapped water in each pos equals to min(left_max[i], right_max[i]) - height[i] */
    for (int i = 0; i < heightSize; i++) {
        volume += left_max[i] < right_max[i] ? left_max[i] - height[i] : right_max[i] - height[i];
    }

    return volume;
}

/* Solution4: Two Pointers
 * We use left_max and right_max to store the left and right max height of each position.
 * The time complexity is O(n), the space complexity is O(1).
 */
int trap4(int* height, int heightSize) {
    int left = 0, right = heightSize - 1, left_max = 0, right_max = 0, volume = 0;

    if (heightSize < 3) {
        return 0;
    }

    while (left < right) {
        if (height[left] < height[right]) {
            left_max = (height[left] > left_max) ? height[left] : left_max;
            volume += left_max - height[left];
            left++;
        } else {
            right_max = (height[right] > right_max) ? height[right] : right_max;
            volume += right_max - height[right];
            right--;
        }
    }

    return volume;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/remove-duplicates-from-sorted-array/description/ */
int removeDuplicates(int* nums, int numsSize) {
    int i = 0, j = 0;

    while (i < numsSize) {
        while (i < numsSize - 1 && nums[i] == nums[i + 1]) {
            i++;
        }

        nums[j++] = nums[i++];
    }

    return j;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/remove-element/description/ */
int removeElement(int* nums, int numsSize, int val) {
    int i = 0, j = 0;

    while (i < numsSize) {
        if (nums[i] != val) {
            nums[j++] = nums[i];
        }
        i++;
    }

    return j;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/move-zeroes/description/ */
void moveZeroes(int* nums, int numsSize) {
    int non_zero_pos = 0;

    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] != 0) {
            nums[non_zero_pos] = nums[i];
            non_zero_pos++;
        }
    }

    while (non_zero_pos < numsSize)
        nums[non_zero_pos++] = 0;

}

/* Solution for leetcode problem: https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/description/ */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int *ret_array = NULL;
    int left = 0, right = numbersSize - 1;

    ret_array = (int*)malloc(sizeof(int) * 2);
    if (ret_array == NULL) {
        printf("twoSum: malloc failed\n");
        return NULL;
    }

    *returnSize = 2;
    while (left < right) {
        if (numbers[left] + numbers[right] == target) {
            ret_array[0] = left + 1;
            ret_array[1] = right + 1;
            return ret_array;
        } else if (numbers[left] + numbers[right] < target) {
            left++;
        } else {
            right--;
        }
    }

    return NULL;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/reverse-string/description/ */
void reverseString(char* s, int sSize) {
    int left = 0, right = sSize - 1;
    char tmp;

    while (left < right) {
        tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
        left++;
        right--;
    }
}