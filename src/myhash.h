#ifndef __MYHASH_H
#define __MYHASH_H

#include <stdbool.h>
#include "uthash.h"

typedef struct {
    int key;
    int num;
    UT_hash_handle hh;
} hash_table_stru;

void hash_add_item(hash_table_stru **hash_table, int key);
bool hash_find_item(hash_table_stru *hash_table, int key);
int hash_get_num(hash_table_stru *hash_table, int key);

#endif