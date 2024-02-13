#include "hashtable.h"
#include "../thirdparty/superfasthash.c"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define LOAD_FACTOR_THRESHOLD 0.75

size_t hash_function(char *key) { return SuperFastHash(key, strlen(key)); }

HashTable *hashtable_create(void) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht == NULL) {
    perror("Failed to create hash table");
    return NULL;
  }

  ht->count = 0;
  ht->size = 0;
  ht->entries = NULL;

  return ht;
}

void hashtable_add(HashTable *ht, char *key, int value) {
  // Resize if necessary
  if (ht->entries == NULL ||
      (float)ht->count / ht->size > LOAD_FACTOR_THRESHOLD) {
    size_t new_size = ht->size == 0 ? 1 : ht->size * 2;

    Entry *new_entries = (Entry *)calloc(new_size, sizeof(Entry));
    if (new_entries == NULL) {
      perror("Failed to resize hash table");
      return;
    }

    for (size_t i = 0; i < ht->size; i++) {
      if (ht->entries[i].key != NULL && !ht->entries[i].removed) {

        size_t index = hash_function(ht->entries[i].key) % new_size;

        while (new_entries[index].key != NULL) {
          index = (index + 1) % new_size;
        }

        new_entries[index].key =
            strdup(ht->entries[i].key); // copy over key to new array
        new_entries[index].value =
            ht->entries[i].value; // copy over value to new array
      }
    }

    free(ht->entries);
    ht->entries = new_entries;
    ht->size = new_size;
  }

  // now actually add new entry

  size_t index = hash_function(key) % ht->size;

  // check if key already exists and is not subject to removal.  if so, just
  // update it
  while (ht->entries[index].key != NULL) {
    if (strcmp(ht->entries[index].key, key) == 0 &&
        !ht->entries[index].removed) {
      ht->entries[index].value = value;
      return;
    }
    index = (index + 1) & ht->size;
  }

  // we didn't find the key, so add it
  ht->entries[index].key = strdup(key);
  ht->entries[index].value = value;
  ht->entries[index].removed = false;
  ht->count++;
}

void hashtable_remove(HashTable *ht, char *key) {
  if (ht->entries == NULL) {
    perror("Cannot remove from empty hash table");
  }

  size_t index = hash_function(key) % ht->size;

  while (ht->entries[index].key != NULL) {
    if (strcmp(ht->entries[index].key, key) == 0) {
      free(ht->entries[index].key);
      ht->entries[index].key = NULL;
      ht->entries[index].removed = true;
      ht->count--;
      return;
    }
    index = (index + 1) & ht->size;
  }
}

void hashtable_destroy(HashTable *ht) {
  for (size_t i = 0; i < ht->size; i++) {
    free(ht->entries[i].key);
  }
  free(ht->entries);
  free(ht);
}
