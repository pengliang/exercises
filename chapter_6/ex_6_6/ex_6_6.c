#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ex_6_1/get_word.h"
#include "ex_6_5/define_macro_hash.h"

static const int kHashSize = 100;
static const int kMaxWord = 100;

enum ParserState{
  kStart,
  kDefine,
  kUnDef,
  kName,
  kDefn
};

void ungets(char *s) {
  int i = 0;

  for (i = strlen(s) - 1; i >= 0; --i) {
    ungetc(s[i], stdin);
  }
}

/* Simple version of #define and #undef processor. */
int main() {
  char word[kMaxWord];
  char *name;
  char defn[kMaxWord];
  LinkNode *p;
  int len = 0, i = 0;
  enum ParserState state = kStart;

  HashTable hash_table[kHashSize];
  HashInit(hash_table, kHashSize);

  memset(word, 0, kMaxWord);
  memset(defn, 0, kMaxWord);

  while (GetWord(word, kMaxWord) != EOF) {
    switch (state) {
      case kStart:
        if (strcmp(word, "#define") == 0) {
          state = kDefine;
        } else if (strcmp(word, "#undef") == 0) {
          state = kUnDef;
        } else if (!isalpha(word[0])) {
          printf("%s", word);
        } else if ((p = HashSearch(hash_table, word)) == NULL) {
          printf("%s", word);
        } else {
          ungets(p->defn);
        }
        break;
      case kDefine:
        if (isalpha(word[0])) {
          name = strdup(word);
          state = kName;
        } else {
          printf("Error: non-alpha name");
          exit(1);
        }
        break;
      case kName:
        if (word[0] == '\n') {
          printf("Error: incomplate define");
          exit(1);
        } else {
          strcpy(defn, word);
          len += strlen(word);
          state = kDefn;
        }
        break;
      case kDefn:
        if (word[0] != '\n' && len < kMaxWord) {
          strcat(defn, word);
          len += strlen(word);
        } else {
          HashInsert(hash_table, name, defn);
          state = kStart;
        }
        break;
      case kUnDef:
        if (isalpha(word[0])) {
          HashDelete(hash_table, name);
          state = kStart;
        } else {
          printf("Error: non-alpha name");
          exit(1);
        }
        break;
    }
  }
  return 0;
}
