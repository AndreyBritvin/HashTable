#ifndef HASHTABLE_H__
#define HASHTABLE_H__

#include "utils.h"
#include "my_list.h"

const size_t av_load_factor = 100;

enum ht_elem_t
{
    NOT_CONTAINS = 0,
    CONTAINS     = 1,
};

struct hash_table_t
{
    my_list* buckets;
    size_t      size;
};

err_code_t ht_ctor(hash_table_t* ht, size_t buckets_amount);
err_code_t ht_dump(hash_table_t* ht);
err_code_t ht_dtor(hash_table_t* ht);
word_counter_t* ht_insert(hash_table_t* ht, char* text);
word_counter_t* ht_find_elem_bucket(hash_table_t* ht, char* text, size_t bucket_num);
word_counter_t* ht_find_elem(hash_table_t* ht, char* text);
err_code_t ht_fill(hash_table_t* ht, char** text_lines, size_t lines_num);

#endif // HASHTABLE_H__
