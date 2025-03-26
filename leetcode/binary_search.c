#include "common.h"

/* Solution for leetcode problem: https://leetcode.cn/problems/search-insert-position/description/ */
int searchInsert(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1, mid;

    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    /* if target is not found, than in the last loop, left == right == mid.
     * if nums[mid] < target, than the position to insert is mid + 1 == left.
     * if nums[mid] > target, than the position to insert is mid == left. */
    return left;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/description/ */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    int *ret_array = NULL;
    int left = 0, right = numsSize - 1, mid;

    ret_array = (int*)malloc(sizeof(int) * 2);
    if (ret_array == NULL) {
        return NULL;
    }
    memset(ret_array, -1, sizeof(int) * 2);
    *returnSize = 2;

    /* First round, find the left bound of the target. */
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (nums[mid] >= target) {    // Move the right bound till nums[mid] < target.
            right = mid - 1;
        } else if (nums[mid] < target) {    // Move the left bound only when nums[mid] < target.
            left = mid + 1;
        }
    }

    if (left < numsSize && nums[left] == target) {
        ret_array[0] = left;
    }

    left = 0;
    right = numsSize - 1;
    /* Second round, find the right bound of the target. */
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (nums[mid] > target) {
            right = mid - 1;
        } else if (nums[mid] <= target) {
            left = mid + 1;
        }
    }

    if (right >= 0 && nums[right] == target) {
        ret_array[1] = right;
    }

    return ret_array;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/search-in-rotated-sorted-array/description/ */
int search(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1, mid;

    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (nums[mid] == target) {
            return mid;
        }

        if (nums[0] <= nums[mid]) {    // The left half is sorted.
            if (nums[0] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {    // The right half is sorted.
            if (nums[mid] < target && target <= nums[numsSize - 1]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    return -1;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/description/ */
int findMin(int* nums, int numsSize) {
    int min = nums[0], left = 0, right = numsSize - 1, mid;

    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (nums[mid] < min) {
            min = nums[mid];
        }

        if (nums[0] <= nums[mid]) {    // The left half is sorted.
            if (nums[0] <= nums[right]) {    // The whole array is sorted.
                return min;
            } else {
                left = mid + 1;
            }
        } else {    // The right half is sorted.
            right = mid - 1;
        }
    }

    return min;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/median-of-two-sorted-arrays/description/ */
int getKthElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int k)
{
    int index1 = 0, index2 = 0, pos = k;    // Find the pos-th element in the merged array of nums1[index1 : nums1Size - 1] and nums2[index2 : nums2Size - 1].
    int newIndex1, newIndex2;

    while (1) {
        if (index1 == nums1Size) {    // All elements in nums1 have been ignored.
            return nums2[index2 + pos - 1];    // return the pos-th element in nums2[index2 : nums2Size - 1].
        } else if (index2 == nums2Size) {    // All elements in nums2 have been visited.
            return nums1[index1 + pos - 1];
        } else if (pos == 1) {    // The smallest element is nums1[index1 : nums1Size - 1] and nums2[index2 : nums2Size - 1]..
            return nums1[index1] < nums2[index2] ? nums1[index1] : nums2[index2];
        }

        /* If nums1[newIndex1] < nums2[newIndex2], then the first (newIndex1 - index1 + 1) elements in nums1[index1 : nums1Size - 1] can be ignored.
         * If nums1[newIndex1] > nums2[newIndex2], then the first (newIndex2 - index2 + 1) elements in nums2[index2 : nums2Size - 1] can be ignored.
         * newIndex = index + pos / 2 - 1, so we can eliminate pos / 2 elements maximum each loop.
         */
        newIndex1 = index1 + pos / 2 - 1 < nums1Size - 1 ? index1 + pos / 2 - 1: nums1Size - 1;
        newIndex2 = index2 + pos / 2 - 1 < nums2Size - 1 ? index2 + pos / 2 - 1: nums2Size - 1;
        if (nums1[newIndex1] < nums2[newIndex2]) {
            pos -= newIndex1 + 1 - index1;    // pos / 2 - 1 has a chance to be 0, so we need to use pos - (newIndex1 - index1 + 1) to make sure pos != 0.
            index1 = newIndex1 + 1;    // The reason same as above, newIndex1 could be equal to index1, so we need to add 1 to newIndex1.
        } else {
            pos -= newIndex2 + 1 - index2;
            index2 = newIndex2 + 1;
        }
    }

    return 0;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int total = nums1Size + nums2Size;

    if (total % 2 == 1) {    // The total number of elements is odd, median is the middle element.
        return getKthElement(nums1, nums1Size, nums2, nums2Size, total / 2 + 1);
    } else {    // The total number of elements is even, median is the average of the two middle elements.
        return (getKthElement(nums1, nums1Size, nums2, nums2Size, total / 2) + getKthElement(nums1, nums1Size, nums2, nums2Size, total / 2 + 1)) / 2.0;
    }
}

/* Solution for leetcode problem: https://leetcode.cn/problems/search-a-2d-matrix/description/ */
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int left = 0, right = matrixSize - 1, mid, *line = NULL;

    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (matrix[mid][0] <= target) {
            if (matrix[mid][*matrixColSize - 1] >= target) {
                break;
            }
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    line = matrix[mid];
    left = 0;
    right = *matrixColSize - 1;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (line[mid] == target) {
            return true;
        } else if (line[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;
}