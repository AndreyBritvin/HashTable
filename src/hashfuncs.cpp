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
#include <stdio.h>
hash_t hash_crc32(void *data, size_t length)
{
    const hash_t POLY = 0x1EDC6F41; // polynome for crc
    const char* bytes = (const char*) data;
    hash_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < length; i++)
    {
        crc ^= bytes[i];
        for (int j = 0; j < 8; j++)
        {
            if (crc & 1)
            {
                crc = (crc >> 1) ^ POLY;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return crc ^ 0xFFFFFFFF;
}
