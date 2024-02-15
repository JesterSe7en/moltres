#include "hashtable.h"
#include "../thirdparty/superfasthash.c"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define LOAD_FACTOR_THRESHOLD 0.75

size_t hash_function(const char *key) {
  return SuperFastHash(key, strlen(key));
}

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

void hashtable_add(HashTable *ht, const char *key, void *value) {
  if (ht == NULL) {
    perror("Cannot add to null hash table");
    return;
  }
  // Resize if necessary; only at (LOAD_FACTOR_THRESHOLD * 100)% capacity
  if (ht->entries == NULL ||
      (float)ht->count / ht->size > LOAD_FACTOR_THRESHOLD) {
    size_t new_size = ht->size == 0 ? 1 : ht->size * 2;

    Entry *new_entries = (Entry *)calloc(new_size, sizeof(Entry));
    if (new_entries == NULL) {
      perror("Failed to resize hash table");
      return;
    }

    for (size_t i = 0; i < ht->size; i++) {
      // only copy over non-removed entries
      if (ht->entries[i].key != NULL && !ht->entries[i].removed) {

        size_t index = hash_function(ht->entries[i].key) % new_size;

        while (new_entries[index].key != NULL) {
          index = (index + 1) % new_size;
        }

        new_entries[index].key = strdup(ht->entries[i].key);
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
      free(ht->entries[index].value);
      ht->entries[index].value = value;
      return;
    }
    index = (index + 1) % ht->size;
  }

  // we didn't find the key, so add it
  ht->entries[index].key = strdup(key);
  ht->entries[index].value = value;
  ht->entries[index].removed = false;
  ht->count++;
}

void hashtable_remove(HashTable *ht, const char *key) {
  if (ht->entries == NULL) {
    perror("Cannot remove from empty hash table");
  }

  size_t index = hash_function(key) % ht->size;

  while (ht->entries[index].key != NULL) {
    // only mark entry as removed if it is the right key; also free key
    if (strcmp(ht->entries[index].key, key) == 0) {
      free(ht->entries[index].key);
      ht->entries[index].key = NULL;
      free(ht->entries[index].value);
      ht->entries[index].removed = true;
      ht->count--;
      return;
    }
    index = (index + 1) & ht->size;
  }
}

void *hashtable_get(HashTable *ht, const char *key) {
  size_t index = hash_function(key) % ht->size;

  while (ht->entries[index].key != NULL) {
    if (strcmp(ht->entries[index].key, key) == 0 &&
        !ht->entries[index].removed) {
      return ht->entries[index].value;
    }
    // linear probing
    index = (index + 1) % ht->size;
  }
  return NULL;
}

void hashtable_destroy(HashTable *ht) {
  for (size_t i = 0; i < ht->size; i++) {
    free(ht->entries[i].key);
  }
  free(ht->entries);
  free(ht);
  ht = NULL;
}

//-------- HASH TABLE ITERATOR ---------

HashTableIterator hashtable_iterator_create(const HashTable *ht) {
  HashTableIterator iterator;
  iterator.ht = ht;
  iterator.current_index = 0;
  return iterator;
}
bool hashtable_iterator_has_next(const HashTableIterator *it) {
  return it->current_index < it->ht->size;
}
Entry *hashtable_iterator_next(HashTableIterator *it) {
  while (it->current_index < it->ht->size) {
    Entry *entry = &it->ht->entries[it->current_index++];
    if (entry->key != NULL && !entry->removed) {
      return entry;
    }
  }

  return NULL;
}
