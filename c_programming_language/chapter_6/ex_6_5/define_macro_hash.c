#include "define_macro_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int hash_table_size;

/* Hash function for a string
 *
 * @param s string
 * @return an unsigned integer
 */
static unsigned Hash(char *s) {
  unsigned hash_val;

  for (hash_val = 0; *s != '\0'; ++s) {
    hash_val = *s + 31 * hash_val;
  }
  return hash_val % hash_table_size;
}

HashTable *HashInit(HashTable *hash_table, int hash_size) {
  int i = 0;

  hash_table_size = hash_size;

  for (i = 0; i < hash_size; ++i) {
    hash_table[i] = NULL;
  }
  return hash_table;
}

LinkNode *HashSearch(HashTable *self, char *name) {
  LinkNode *p = self[Hash(name)];

  for (; p != NULL; p = p->next) {
    if (strcmp(name, p->name) == 0) {
      return p;
    }
  }
  return NULL;
}

LinkNode *HashInsert(HashTable *self, char *name, char *defn) {
  unsigned hash_val;
  LinkNode *p = NULL;

  if ((p = HashSearch(self, name)) == NULL) {
    // new element
    p = (LinkNode *) malloc(sizeof(*p));

    if (!p || !(p->name = strdup(name))) {
      return NULL;
    }
    hash_val = Hash(name);
    p->next = self[hash_val];
    self[hash_val] = p;
  } else {
    // old element, replace the defination
    free((void *) p->defn);
  }
  if ((p->defn = strdup(defn)) == NULL) {
    return NULL;
  }
  return p;
}

void HashDelete(HashTable *self, char *name) {
  int hash_val;
  LinkNode *prev = NULL, *p = NULL;

  hash_val = Hash(name);

  for (p = self[hash_val]; p != NULL; p = p->next) {
    if (strcmp(name, p->name) == 0) {
      break;
    }
    prev = p;
  }

  if (p != NULL) {
    if (prev == NULL) {
      self[hash_val] = p->next;
    } else {
      prev->next = p ->next;
    }
    free((void *) p->name);
    free((void *) p->defn);
    free((void *) p);
  }
}
