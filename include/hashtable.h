#ifndef HASHTABLE_H__
#define HASHTABLE_H__

#include "utils.h"
#include "my_list.h"

const size_t av_load_factor = 15;

struct hash_table_t
{
    my_list* buckets;
    size_t      size;
};

err_code_t ht_ctor(hash_table_t* ht, size_t buckets_amount);
err_code_t ht_dump(hash_table_t* ht);
err_code_t ht_dtor(hash_table_t* ht);


#endif // HASHTABLE_H__
