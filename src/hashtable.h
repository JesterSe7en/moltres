#ifndef INCLUDE_SRC_HASHTABLE_H_
#define INCLUDE_SRC_HASHTABLE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Entry {
  char *key;
  void *value;
  bool removed;
} Entry;

typedef struct HashTable {
  Entry *entries;
  size_t size;
  size_t count;
} HashTable;

typedef struct HashTableIterator {
  const HashTable *ht;
  size_t current_index;
} HashTableIterator;

HashTable *hashtable_create(void);
void hashtable_remove(HashTable *ht, const char *key);
void hashtable_add(HashTable *ht, const char *key, void *value);
void *hashtable_get(HashTable *ht, const char *key);
void hashtable_destroy(HashTable *ht);

HashTableIterator hashtable_iterator_create(const HashTable *ht);
bool hashtable_iterator_has_next(const HashTableIterator *it);
Entry *hashtable_iterator_next(HashTableIterator *it);

#endif // INCLUDE_SRC_HASHTABLE_H_
