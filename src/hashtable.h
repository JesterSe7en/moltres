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
void hashtable_remove(HashTable *, char *);
void hashtable_add(HashTable *, char *, void *);
void hashtable_destroy(HashTable *);

#endif // INCLUDE_SRC_HASHTABLE_H_
