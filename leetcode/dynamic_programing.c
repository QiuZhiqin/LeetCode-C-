#include "common.h"

/* Solution for leetcode problem: https://leetcode-cn.com/problems/coin-change/description/ */
int coinChange(int* coins, int coinsSize, int amount) {
    int *dpHelp = NULL;

    dpHelp = (int*)malloc((amount + 1) * sizeof(int));
    if (dpHelp == NULL) {
        return -1;
    }

    dpHelp[0] = 0;
    for (int i = 1; i < amount + 1; i++) {
        dpHelp[i] = amount + 1;
        for (int j = 0; j < coinsSize; j++) {
            if (i - coins[j] < 0) {
                continue;
            }

            dpHelp[i] = dpHelp[i] < dpHelp[i - coins[j]] + 1 ? dpHelp[i] : dpHelp[i - coins[j]] + 1;
        }
    }

    return dpHelp[amount] == amount + 1 ? -1 : dpHelp[amount];
}

/* Solution for leetcode problem: https://leetcode.cn/problems/climbing-stairs/description/ */
int climbStairs(int n) {
    int dp[50] = {0};

    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

/* Solution for leetcode problem: https://leetcode.cn/problems/house-robber/description/ */
int rob(int* nums, int numsSize) {
    int *dp = NULL;

    if (numsSize == 0) {
        return 0;
    } else if (numsSize == 1) {
        return nums[0];
    }

    dp = (int*)malloc((numsSize) * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    dp[0] = nums[0];
    dp[1] = nums[1] > nums[0] ? nums[1] : nums[0];
    for (int i = 2; i < numsSize; i++) {
        dp[i] = dp[i - 1] > dp[i - 2] + nums[i] ? dp[i - 1] : dp[i - 2] + nums[i];
    }

    return dp[numsSize - 1];
}

/* Solution for leetcode problem: https://leetcode.cn/problems/perfect-squares/description/ */
int numSquares(int n) {
    int dp[10001] = {0};

    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = i;
        for (int j = 1; j * j <= i; ++j) {
            dp[i] = dp[i] < dp[i - j * j] + 1 ? dp[i] : dp[i - j * j] + 1;
        }
    }

    return dp[n];
}

/* Solution for leetcode problem: https://leetcode.cn/problems/longest-increasing-subsequence/description/ */
int lengthOfLIS(int* nums, int numsSize) {
    int dp[2500] = {0}, max = 0;

    for (int i = 0; i < numsSize; ++i) {
        dp[i] = 1;    // dp[i] means the length of the longest increasing subsequence that ends with nums[i].
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
            }
        }
        max = max > dp[i] ? max : dp[i];
    }

    return max;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/maximum-product-subarray/description/ */
int maxProduct(int* nums, int numsSize) {
    int max[25000] = {0}, min[25000] = {0}, result = nums[0];

    if (numsSize == 1) {
        return result;
    }

    max[0] = nums[0];
    min[0] = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        max[i] = nums[i];
        min[i] = nums[i];
        max[i] = max[i] > max[i - 1] * nums[i] ?
                 max[i] > min[i - 1] * nums[i] ? max[i] : min[i - 1] * nums[i] :
                 max[i - 1] * nums[i] > min[i - 1] * nums[i] ? max[i - 1] * nums[i] : min[i - 1] * nums[i];
        min[i] = min[i] < min[i - 1] * nums[i] ?
                 min[i] < max[i - 1] * nums[i] ? min[i] : max[i - 1] * nums[i] :
                 min[i - 1] * nums[i] < max[i - 1] * nums[i] ? min[i - 1] * nums[i] : max[i - 1] * nums[i];
        result = result > max[i] ? result : max[i];
    }

    return result;
}

/* https://leetcode.cn/problems/partition-equal-subset-sum/description/ */
bool canPartitionVersion(int* nums, int numsSize) {
    int sum = 0, target;
    bool *dp[250] = {NULL};

    if (numsSize < 2) {
        return false;
    }

    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }

    target = sum / 2;
    if (sum % 2 != 0) {
        return false;
    }

    for (int i = 0; i < numsSize; i++) {
        /* If there is a number greater than target, than the sum of the rest of the numbers must be less than target. */
        if (nums[i] > target) {
            return false;
        } else if (nums[i] == target) {
            return true;
        }

        dp[i] = (bool*)malloc((target + 1) * sizeof(bool));
        if (dp[i] == NULL) {
            return false;
        }
        memset(dp[i], 0, (target + 1) * sizeof(bool));
        /* If we pick none of the numbers, the sum of the subset is surely 0. */
        dp[i][0] = true;
    }
    /* If we pick the first number, the sum of the subset is surely nums[0]. */
    dp[0][nums[0]] = true;

    /* dp[i][j] means we can pick some numbers from nums[0] to nums[i] to make the sum of the subset equal to j. */
    for (int i = 1; i < numsSize; ++i) {
        for (int j = 1; j <= target; ++j) {
            if (j < nums[i]) {
                /* If taget sum(j) is less than nums[i], we can't pick nums[i]. */
                dp[i][j] = dp[i - 1][j];
            } else {
                /* We can choose to pick nums[i] or not. */
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i]];
            }
        }
    }

    return dp[numsSize - 1][target];
}

bool canPartitionVersion2(int* nums, int numsSize) {
    int sum = 0, target;
    bool *dp = NULL;

    if (numsSize < 2) {
        return false;
    }

    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }

    target = sum / 2;
    if (sum % 2 != 0) {
        return false;
    }

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > target) {
            return false;
        } else if (nums[i] == target) {
            return true;
        }
    }

    dp = (bool*)malloc((target + 1) * sizeof(bool));
    if (dp == NULL) {
        return false;
    }
    memset(dp, 0, (target + 1) * sizeof(bool));
    /* If we pick none of the numbers, the sum of the subset is surely 0. */
    dp[0] = true;

    /* dp[j] means we can pick some numbers from nums[0] to nums[i] to make the sum of the subset equal to j. */
    for (int i = 1; i < numsSize; ++i) {
        for (int j = target; j >= nums[i]; --j) {
            dp[j] |= dp[j - nums[i]];
        }
    }

    return dp[target];
}

/* Solution for leetcode problem: https://leetcode.cn/problems/longest-valid-parentheses/description/*/
int longestValidParentheses(char* s) {
    int dp[30000] = {0}, max = 0, len = 0;

    if (s == NULL || strlen(s) == 0) {
        return 0;
    }

    len = strlen(s);
    /* dp[i] means the length of the longest valid parentheses that ends with s[i]. */
    for (int i = 1; i < len; ++i) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                dp[i] = (i - 2 >= 0 ? dp[i - 2] : 0) + 2;
            } else if (s[i - 1] == ')') {
                /* i - dp[i - 1] - 1 means the index of the last '(' that can be matched with s[i]. */
                if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(') {
                    /* If s[i - dp[i - 1] - 1] == '(', we can add the length of the longest valid parentheses that ends with s[i - dp[i - 1] - 2]. */
                    dp[i] = dp[i - 1] + (i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
            }
        }
        max = max > dp[i] ? max : dp[i];
    }

    return max;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/word-break/description/ */
bool wordBreak(char* s, char** wordDict, int wordDictSize) {
    int len = strlen(s), i, j;
    bool *dp = NULL;

    dp = (bool*)malloc((len + 1) * sizeof(bool));
    if (dp == NULL) {
        return false;
    }
    memset(dp, 0, (len + 1) * sizeof(bool));
    dp[0] = true;
    for (i = 1; i < len + 1; ++i) {
        for (j = 0; j < wordDictSize; ++j) {
            int wordLen = strlen(wordDict[j]);
            if (i >= wordLen && strncmp(s + i - wordLen, wordDict[j], wordLen) == 0) {
                dp[i] = dp[i] || dp[i - wordLen];
            }
        }
    }

    return dp[len];
}