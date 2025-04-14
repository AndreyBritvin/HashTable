#include "hashfuncs.h"

hash_t hash_ascii_sum(void *to_hash, size_t size_to_hash)
{
    hash_t hash = 0;

    for (size_t i = 0; i < size_to_hash; i++)
    {
        hash += ((char *) to_hash)[i];
    }

    return hash;
}
