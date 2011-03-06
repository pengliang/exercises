#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const int kMaxDesc = 1000;
const int kMaxToken = 10;

int main() {
  char type_qual[kMaxToken];
  char type_spec[kMaxToken];
  char var_name[kMaxToken];
  char desc[kMaxDesc];

  memset(type_qual, 0, kMaxToken);
  memset(type_spec, 0, kMaxToken);
  memset(var_name, 0, kMaxToken);
  memset(desc, 0, kMaxDesc);

  ParseDeclaration(type_qual, type_spec, var_name, desc);

  return 0;
}


inline void Error(const char *msg) {
  printf("%s\n", msg);
  exit(1);
}

void ungets(const char *s) {
  int i = 0;
  int len = strlen(s);

  for (i = len - 1; i >= 0; --i) {
    ungetc(s[i], stdin);
  }
}

void PrintDesc(char *type_qual, char *type_spec,
               char *var_name, char *desc) {

  if (*var_name == '\0') {
    Error("no identifier");
  }

  if (*type_qual == '\0') {
    printf("%s: %s %s\n", var_name, desc, type_spec);
  } else {
    printf("%s: %s %s %s\n", var_name, desc, type_qual, type_spec);
  }

  memset(var_name, 0, kMaxToken);
  memset(desc, 0, kMaxDesc);
}

