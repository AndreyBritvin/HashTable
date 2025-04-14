#include "hashtable.h"
#include "stdio.h"
#include "stdlib.h"


int main()
{
    hash_table_t my_ht = {};

    ht_ctor(&my_ht, 20);
    ht_insert(&my_ht, "12345");
    ht_dump(&my_ht);
    ht_dtor(&my_ht);

    return EXIT_SUCCESS;
}
