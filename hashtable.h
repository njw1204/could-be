#pragma once

#include <stdio.h>
#include <stdint.h>
#include "yynode.h"
#include "linkedlist.h"

#define HASH_TABLE_SIZE 10007
#define HASH_SEED 99991

typedef struct {
    List list[HASH_TABLE_SIZE];
} HashTable;

HashTable createHashTable();
void insertToHashTable(HashTable *table, const char *key, YYNode node);
YYNode *findFromHashTable(HashTable *table, const char *key);
uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed);
