#ifndef __COMMON_H
#define __COMMON_H

static inline void swap(int *a, int *b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}

unsigned int get_maxbits(unsigned int *data, unsigned int arry_size);

unsigned int get_digit(unsigned int num, unsigned int position);

#endif