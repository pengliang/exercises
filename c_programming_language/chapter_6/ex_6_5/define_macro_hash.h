#ifndef K_AND_R_ASSIGNMENTS_EX_6_5_DEFINE_MACRO_HASH_H
#define K_AND_R_ASSIGNMENTS_EX_6_5_DEFINE_MACRO_HASH_H

struct LinkNode {
  char *name;
  char *defn;
  struct LinkNode *next;
};

typedef struct LinkNode LinkNode;
typedef struct LinkNode *HashTable;

/* Initializes the hash table
 *
 * @param hash_table address of hash table
 * @param hash_size length of the hash table
 * @return hash table's pointer
 */
HashTable *HashInit(HashTable *hash_table, int hash_size);

/* Finds the name in the hash table
 *
 * @param self hash table's address
 * @param name to be searched
 * @return pointer to the link node or
 *         NULL if it is not found.
 */
LinkNode *HashSearch(HashTable *self, char *name);

/* Inserts a node in hash table, if it is already in,
 * update its defn member.
 *
 * @param self hash table's address
 * @param name string
 * @param defn string
 * @return pointer the node
 * */
LinkNode *HashInsert(HashTable *self, char *name, char *defn);

/* Deletes the node from hash table
 *
 * @param self hash table's address
 * @param name the name member's value of link node
 */
void HashDelete(HashTable *self, char *name);

#endif // K_AND_R_ASSIGNMENTS_EX_6_5_DEFINE_MACRO_HASH_H
