#include "hashtable.h"
#include "stdio.h"
#include "stdlib.h"


int main()
{
    hash_table_t my_ht = {};

    ht_ctor(&my_ht, 20);
    // ht_insert(&my_ht, "12345");
    // ht_insert(&my_ht, "5678");
    // ht_insert(&my_ht, "03345");
    // ht_insert(&my_ht, "03345");
    char* text_lines[] = {"12345", "5678", "1234", "12345"};
    ht_fill(&my_ht, text_lines, sizeof(text_lines) / sizeof(char*));
    ht_dump(&my_ht);
    ht_dtor(&my_ht);

    return EXIT_SUCCESS;
}
