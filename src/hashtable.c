#include "hashtable.h"
#include "../thirdparty/superfasthash.c"
#include <string.h>

HashTable *hashtable_create(void) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht == NULL) {
    fprintf(stderr, "Error allocating memory for hash table\n");
    return NULL;
  }

  ht->count = 0;
  ht->size = 0;
  ht->entries = NULL;

  return ht;
}

void hashtable_remove(HashTable *, char *) {
  // TODO: implement me!
}

void hashtable_add(HashTable *, char *, int) {

  // TODO: implement me!
}

void hashtable_destroy(HashTable *) {
  // TODO: implement me!
}

size_t hash_function(const char *key) {
  return SuperFastHash(key, strlen(key));
}
