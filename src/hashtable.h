#ifndef MOLTRES_SRC_HASHTABLE_H_
#define MOLTRES_SRC_HASHTABLE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * @struct Entry
 * @brief Represents an entry in the hash table.
 */
typedef struct Entry {
  char *key;          /**< Key associated with the entry */
  void *value;        /**< Value associated with the entry */
  bool removed;       /**< Flag indicating if the entry has been removed */
} Entry;

/**
 * @struct HashTable
 * @brief Represents a hash table.
 */
typedef struct HashTable {
  Entry *entries;     /**< Array of entries in the hash table */
  size_t size;        /**< Total size of the hash table */
  size_t count;       /**< Number of entries in the hash table */
} HashTable;

/**
 * @struct HashTableIterator
 * @brief Represents an iterator for the hash table.
 */
typedef struct HashTableIterator {
  const HashTable *ht;       /**< Pointer to the hash table */
  size_t current_index;      /**< Current index of the iterator */
} HashTableIterator;

/**
 * @brief Creates a new hash table.
 * @return Pointer to the newly created hash table.
 */
HashTable *HashtableCreate(void);

/**
 * @brief Removes an entry with the specified key from the hash table.
 * @param ht Pointer to the hash table.
 * @param key Key of the entry to be removed.
 */
void HashtableRemove(HashTable *ht, const char *key);

/**
 * @brief Adds a new entry to the hash table.
 * @param ht_ptr Pointer to the pointer to the hash table.
 * @param key Key of the entry to be added.
 * @param value Value of the entry to be added.
 */
void HashtableAdd(HashTable **ht_ptr, const char *key, void *value);

/**
 * @brief Retrieves the value associated with the specified key from the hash table.
 * @param ht_ptr Pointer to the pointer to the hash table.
 * @param key Key of the entry to retrieve the value for.
 * @return Pointer to the value associated with the key, or NULL if not found.
 */
void *HashtableGet(HashTable **ht_ptr, const char *key);

/**
 * @brief Destroys the hash table and frees associated memory.
 * @param ht Pointer to the hash table.
 */
void HashtableDestroy(HashTable *ht);

/**
 * @brief Creates an iterator for the hash table.
 * @param ht Pointer to the hash table.
 * @return Hash table iterator.
 */
HashTableIterator HashtableIteratorCreate(const HashTable *ht);

/**
 * @brief Checks if the hash table iterator has more entries to iterate over.
 * @param it Pointer to the hash table iterator.
 * @return True if there are more entries, false otherwise.
 */
bool HashtableIteratorHasNext(const HashTableIterator *it);

/**
 * @brief Retrieves the next entry from the hash table iterator.
 * @param it Pointer to the hash table iterator.
 * @return Pointer to the next entry.
 */
Entry *HashtableIteratorNext(HashTableIterator *it);

#endif // MOLTRES_SRC_HASHTABLE_H_
