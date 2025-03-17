#include <stdlib.h>
#include <stdbool.h>

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