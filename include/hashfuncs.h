#ifndef HASHFUNCS_H__
#define HASHFUNCS_H__

#include <stdlib.h>

typedef unsigned long long hash_t;

hash_t hash_ascii_sum(void *to_hash, size_t size_to_hash);

#endif // HASHFUNCS_H__
