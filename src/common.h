#ifndef __COMMON_H
#define __COMMON_H

static inline void swap(int *a, int *b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}

#endif