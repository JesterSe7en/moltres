#ifndef INCLUDE_SRC_HASHTABLE_H_
#define INCLUDE_SRC_HASHTABLE_H_

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *key;
  int value;
} Entry;

typedef struct {
  Entry *entries;
  size_t size;
  size_t count;
} HashTable;

HashTable *hashtable_create(void);
void hashtable_remove(HashTable *, char *);
void hashtable_add(HashTable *, char *, int);
void hashtable_destroy(HashTable *);

#endif // INCLUDE_SRC_HASHTABLE_H_
