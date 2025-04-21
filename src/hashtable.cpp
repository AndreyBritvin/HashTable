#include "hashtable.h"
#include "utils.h"
#include <assert.h>
#include "hashfuncs.h"
#include <string.h>
#include <immintrin.h>

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
        PRINT("Bucket #%5zu: ", i);
        print_list(&ht->buckets[i]);
        PRINT(" \n");
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

word_counter_t* ht_insert(hash_table_t* ht, char* text)
{
    assert(ht);
    assert(text);
    // printf("IN ht_insert text = %p\n", text);
    hash_t hash = hash_crc32(text, strlen(text));
    size_t bucket_num = hash % ht->size;
    my_list* list_to_search = &ht->buckets[bucket_num];
    // printf("Line = %s hash = %llu\n", text, hash);

    word_counter_t* bucket_elem = ht_find_elem_bucket(ht, text, bucket_num);

    if (bucket_elem == NULL)
    {
        word_counter_t to_add = {text, 0};
        list_insert(list_to_search, get_tail(list_to_search), to_add);
        // printf("Addr of inserted = %p\n", ht_find_elem_bucket(ht, text, bucket_num));
        // printf("%d - %s\n", list_to_search->size, text);
        // return NOT_CONTAINS;
    }
    // printf("Addr of found = %p\n", ht_find_elem_bucket(ht, text, bucket_num));
    bucket_elem = ht_find_elem_bucket(ht, text, bucket_num);

    return bucket_elem;
}

word_counter_t* ht_find_elem_bucket(hash_table_t* ht, char* text, size_t bucket_num)
{
    assert(ht);
    assert(text);

    my_list list_to_search = ht->buckets[bucket_num];
// printf("Line = %s bucket num = %u\n", text, bucket_num);
    for (size_t i = 0; i < list_to_search.capacity; i++) // TODO: make list founder via PREV and NEXT nodes
    {
        if (list_to_search.data[i].word && !strcmp(text, list_to_search.data[i].word))
        {
            return &list_to_search.data[i];
        }
    }

    return NULL;
}


err_code_t ht_fill(hash_table_t* ht, char** text_lines, size_t lines_num)
{
    for (size_t i = 0; i < lines_num; i++)
    {
        word_counter_t* elem_in_ht = ht_insert(ht, text_lines[i]); //TODO: make check if there enough capacity to prevent not found===null error
                        elem_in_ht->count += 1;
    }

    return OK;
}

// All words should be 32 bytes (or n butes and others with zeros)
// Return only equal or not equal
int my_avx_strcmp(const char* str1, const char* str2)
{
    __m256i string_1 = _mm256_loadu_si256((__m256i *) str1);
    __m256i string_2 = _mm256_loadu_si256((__m256i *) str2);
    __m256i equal    = _mm256_cmpeq_epi64(string_1, string_2);
    int result = _mm256_movemask_epi8(equal);

    return ~result;
}

#undef LIST_IS_PTR
#include "list_dsl.h"
word_counter_t* ht_find_elem(hash_table_t* ht, char* text)
{
    assert(ht);
    assert(text);

    hash_t hash = hash_crc32(text, strlen(text));
    // size_t bucket_num = hash % ht->size;
    size_t bucket_num = 0;
    asm volatile(
    "and %2, %1\n"              // instruction
    : "=r" (bucket_num)         // output
    : "r"  ((size_t) hash),     //input
      "r"  (ht->size - 1)
    );

    my_list list = ht->buckets[bucket_num];

    labels_t    previous_next   = NEXT[0];
    while (NEXT[previous_next] != NEXT[0])
    {
        // printf("%s(%u) ", DATA[previous_next].word, DATA[previous_next].count);
        if (!my_avx_strcmp(text, DATA[previous_next].word))
        {
            return &DATA[previous_next];
        }

        previous_next = NEXT[previous_next];
    }

    return NULL;
}
#include "undef_dsl.h"
