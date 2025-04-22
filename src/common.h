#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX(a, b) ((b) > (a) ? (b) : (a))

static inline void swap(int *a, int *b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}

unsigned int get_maxbits(unsigned int *data, unsigned int arry_size);

unsigned int get_digit(unsigned int num, unsigned int position);

#ifdef __cplusplus
}
#endif
#endif