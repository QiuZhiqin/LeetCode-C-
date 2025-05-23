#include "common.h"

/* Get the maximum weight of the array */
unsigned int get_maxbits(unsigned int *data, unsigned int arry_size)
{
    unsigned int max = 0;
    unsigned int digit = 0;

    for (unsigned int i = 0; i < arry_size; ++i) {
        if (data[i] > max) {
            max = data[i];
        }
    }

    while (max) {
        digit++;
        max /= 10;
    }

    return digit;
}

unsigned int get_digit(unsigned int num, unsigned int position)
{
    for (unsigned int i = 0; i < position; ++i) {
        num /= 10;
    }

    return num % 10;
}