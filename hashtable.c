#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "yynode.h"
#include "linkedlist.h"
#include "hashtable.h"

HashTable createHashTable() {
    HashTable table = {NULL};
    return table;
}

void insertToHashTable(HashTable *table, const char *key, YYNode node) {
    int hash = murmur3_32(key, strlen(key), HASH_SEED) % HASH_TABLE_SIZE;
    node.sParam[7] = malloc(BUF_SIZE);
    strncpy(node.sParam[7], key, BUF_SIZE);
    appendToList(&(table->list[hash]), node);
}

YYNode *findFromHashTable(HashTable *table, const char *key) {
    int hash = murmur3_32(key, strlen(key), HASH_SEED) % HASH_TABLE_SIZE;
    List L = table->list[hash];
    ListNode *curr = L;

    while (curr) {
        if (strcmp(curr->data.sParam[7], key) == 0) {
            return &(curr->data);
        }
        curr = nextNode(L, curr);
    }

    return NULL;
}

int removeFromHashTable(HashTable *table, const char *key) {
    int hash = murmur3_32(key, strlen(key), HASH_SEED) % HASH_TABLE_SIZE;
    ListNode *curr = table->list[hash];

    while (curr) {
        if (strcmp(curr->data.sParam[7], key) == 0) {
            removeFromList(&(table->list[hash]), curr);
            return 1;
        }
        curr = nextNode(table->list[hash], curr);
    }

    return 0;
}

uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed) {
    uint32_t h = seed;
    if (len > 3) {
        size_t i = len >> 2;
        do {
            uint32_t k;
            memcpy(&k, key, sizeof(uint32_t));
            key += sizeof(uint32_t);
            k *= 0xcc9e2d51;
            k = (k << 15) | (k >> 17);
            k *= 0x1b873593;
            h ^= k;
            h = (h << 13) | (h >> 19);
            h = h * 5 + 0xe6546b64;
        } while (--i);
    }
    if (len & 3) {
        size_t i = len & 3;
        uint32_t k = 0;
        do {
            k <<= 8;
            k |= key[i - 1];
        } while (--i);
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        h ^= k;
    }
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}
