#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "types.h"

typedef struct HashNode {
    Paket data;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode *buckets[HASH_SIZE];
} HashTable;

void initHashTable(HashTable *ht);
unsigned int hashFunction(const char *resi);
void insertHash(HashTable *ht, Paket p);
Paket *searchHash(const HashTable *ht, const char *resi);
void freeHashTable(HashTable *ht);

#endif
