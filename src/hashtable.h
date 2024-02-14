#ifndef INCLUDE_SRC_HASHTABLE_H_
#define INCLUDE_SRC_HASHTABLE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *key;
  void *value;
  bool removed;
} Entry;

typedef struct {
  Entry *entries;
  size_t size;
  size_t count;
} HashTable;

HashTable *hashtable_create(void);
void hashtable_remove(HashTable *ht, const char *key);
void hashtable_add(HashTable *ht, const char *key, void *value);
void *hashtable_get(HashTable *ht, const char *key);
void hashtable_destroy(HashTable *ht);

#endif // INCLUDE_SRC_HASHTABLE_H_
