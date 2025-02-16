#include "myhash.h"

void hash_add_item(hash_table_stru **hash_table, int key)
{
    hash_table_stru *s;

    HASH_FIND_INT(*hash_table, &key, s);
    if (s == NULL) {
        s = (hash_table_stru *)malloc(sizeof(hash_table_stru));
        s->key = key;
        s->num = 1;
        HASH_ADD_INT(*hash_table, key, s);
    } else {
        s->num++;
    }
}

bool hash_find_item(hash_table_stru *hash_table, int key)
{
    hash_table_stru *s;

    HASH_FIND_INT(hash_table, &key, s);
    if (s == NULL) {
        return false;
    } else {
        return true;
    }
}

int hash_get_num(hash_table_stru *hash_table, int key)
{
    hash_table_stru *s;

    HASH_FIND_INT(hash_table, &key, s);
    if (s == NULL) {
        return 0;
    } else {
        return s->num;
    }
}