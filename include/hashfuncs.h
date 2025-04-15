#ifndef HASHFUNCS_H__
#define HASHFUNCS_H__

#include <stdlib.h>

typedef unsigned long long hash_t;

hash_t hash_ascii_sum(void *to_hash, size_t size_to_hash);
hash_t hash_crc32(void *data, size_t length);

#endif // HASHFUNCS_H__
