#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

void initHashTable(HashTable *ht) {
    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        ht->buckets[i] = NULL;
    }
}

unsigned int hashFunction(const char *resi) {
    unsigned int hash = 0;
    while (*resi) {
        hash = (hash * 31) + (unsigned char)(*resi++);
    }
    return hash % HASH_SIZE;
}

void insertHash(HashTable *ht, Paket p) {
    unsigned int idx = hashFunction(p.resi);
    HashNode *node = (HashNode *)malloc(sizeof(HashNode));
    node->data = p;
    node->next = ht->buckets[idx]; /* Chaining untuk menangani collision */
    ht->buckets[idx] = node;
}

Paket *searchHash(const HashTable *ht, const char *resi) {
    unsigned int idx = hashFunction(resi);
    HashNode *curr = ht->buckets[idx];
    while (curr) {
        if (strcmp(curr->data.resi, resi) == 0) {
            return &curr->data;
        }
        curr = curr->next;
    }
    return NULL;
}

void freeHashTable(HashTable *ht) {
    int i;
    HashNode *curr, *temp;
    for (i = 0; i < HASH_SIZE; i++) {
        curr = ht->buckets[i];
        while (curr) {
            temp = curr;
            curr = curr->next;
            free(temp);
        }
        ht->buckets[i] = NULL;
    }
}
