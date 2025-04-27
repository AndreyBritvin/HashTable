#include "hashtable.h"
#include "read_text.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

#define TIME_MEASURE(...)                                               \
        unsigned int lo = 0, hi = 0;                                    \
        __asm__ __volatile__ ("rdtscp" : "=a" (lo), "=d" (hi));         \
        timestamp_t time_begin = ((timestamp_t)hi << 32) | lo;          \
                                                                        \
        __VA_ARGS__                                                     \
                                                                        \
        __asm__ __volatile__ ("rdtscp" : "=a" (lo), "=d" (hi));         \
        timestamp_t time_end = ((timestamp_t)hi << 32) | lo;            \
        printf("Measured time is %10llu ticks\n", time_end - time_begin);

typedef unsigned long long timestamp_t;

int main()
{
    char* text = NULL;
    char** text_lines = NULL;

    // "txt_parser/war_and_peace_words.txt"
    int lines_num = parse_lines("txt_parser/war_and_peace_words.txt", &text, &text_lines);

    hash_table_t my_ht = {};

    ht_ctor(&my_ht, 32768); // should be 2^n
    // ht_insert(&my_ht, "12345");
    // ht_insert(&my_ht, "5678");
    // ht_insert(&my_ht, "03345");
    // ht_insert(&my_ht, "03345");
    // printf("Lines num = %u\n", lines_num);
    // for (size_t i = 0; i < lines_num; i++)
    // {
    //     printf("%p = %s\n", &text_lines[i], text_lines[i]);
    // }
    ht_fill(&my_ht, text_lines, lines_num - 10);

    // ht_dump(&my_ht);

    size_t summ = 0;
    TIME_MEASURE
    (
    for (size_t i = 0; i < 100000 * 4; i += 4)
    {
        word_counter_t* ht_data = ht_find_elem(&my_ht, text_lines[i]);
        // printf("i = %u, %p\n", i, ht_data);
        // printf("%s (%u)\n", ht_data->word, ht_data->count);
        summ += ht_data->count;
    }
    )
    printf("Resulted counts of every ... word is %u\n", summ);

    ht_dtor(&my_ht);
    free(text_lines);
    free(text);

    return EXIT_SUCCESS;
}
