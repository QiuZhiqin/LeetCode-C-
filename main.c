#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "alg_sort.h"
#include "alg_linked_list.h"
#include "alg_binary_tree.h"
#include "myhash.h"

int numSquares(int n);
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target);

int main(void)
{
    int data[3][4] = {{1,3,5,7}, {10,11,16,20}, {23,30,34,60}};
    int colSzie = 4;
    bool result = searchMatrix((int**)data, 3, &colSzie, 3);

    return 0;
}