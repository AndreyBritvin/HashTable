#include "hashtable.h"
#include "utils.h"
#include <assert.h>
#include "hashfuncs.h"
#include <string.h>

err_code_t ht_ctor(hash_table_t* ht, size_t buckets_amount)
{
    assert(ht);

    my_list* lists = (my_list *) calloc(buckets_amount, sizeof(my_list));
    if (!lists)
    {
        return ERROR_LIST_ALLOCATION_MEMORY;
    }

    ht->buckets = lists;
    ht->size    = buckets_amount;

    for (size_t i = 0; i < buckets_amount; i++)
    {
        list_ctor(&ht->buckets[i], av_load_factor);
    }

    return OK;
}

#define PRINT(...) fprintf(stdout, __VA_ARGS__);
err_code_t ht_dump(hash_table_t* ht)
{
    assert(ht);

    PRINT("------begin------\n");
    PRINT("Hash table ... \n"); // TODO: add name and place of ctor, also function etc as in list
    PRINT("Buckets amount: %zu\n", ht->size);
    PRINT("Every list containment:\n");
    for (size_t i = 0; i < ht->size; i++)
    {
        PRINT("Bucket #%5zu:\n", i);
        print_list(&ht->buckets[i]);
    }

    PRINT("-------end-------\n");

    return OK;
}
#undef PRINT

err_code_t ht_dtor(hash_table_t* ht)
{
    assert(ht);

    for (size_t i = 0; i < ht->size; i++)
    {
        list_dtor(&ht->buckets[i]);
    }

    ht->size = 0;
    free(ht->buckets); ht->buckets = NULL;

    return OK;
}

err_code_t ht_insert(hash_table_t* ht, char* text)
{
    assert(ht);
    assert(text);

    hash_t hash = hash_ascii_sum(text, strlen(text));
    // printf("Hash of %s = %llu\n", text, hash);
    size_t bucket_num = hash % ht->size;

    list_insert(&ht->buckets[bucket_num], get_tail(&ht->buckets[bucket_num]), strlen(text));

    return OK;
}
