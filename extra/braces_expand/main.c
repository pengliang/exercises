#include <stdio.h>
#include "braces_expand.h"
#include "string_vec.h"

int main(int argc, char *argv[]) {
  while (--argc > 0) {
    char **result = NULL;
    result = ExpandBrace(*++argv);
    StrVecPrint(result);
    StrVecFree(result);
  }
  return 0;
}
