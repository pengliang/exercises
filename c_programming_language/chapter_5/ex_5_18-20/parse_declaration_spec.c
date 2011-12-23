#include "parse_declaration_spec.h"
#include <string.h>
#include "main.h"
#include "get_token.h"

static const char *kNoTypeSpec = "no data type specifier";
static const char *kMoreTypeQual = "too many type qualifiers";

enum ParseState {
  kTypeQual,
  kTypeSpec
};

void ParseDeclarationSpec(char *type_qual, char *type_spec) {
  char token[kMaxToken];
  int token_type = 0;
  enum ParseState state = kTypeQual;

  while ((token_type = GetToken(token))) {
    switch (state) {
      case kTypeQual:
        if (IsTypeQual(token)) {
          strcpy(type_qual, token);
          state = kTypeSpec;
        } else if (IsTypeSpec(token)) {
          strcpy(type_spec, token);
          return;
        } else {
          Error(kNoTypeSpec);
        }
        break;
      case kTypeSpec:
        if (IsTypeQual(token)) {
          Error(kMoreTypeQual);
        } else if (IsTypeSpec(token)) {
          strcpy(type_spec, token);
          return;
        } else {
          Error(kNoTypeSpec);
        }
        break;
    }
  }
}

static int compare(char **s, char **t) {
  return strcmp(*s, *t);
}

int IsTypeSpec(char *token) {
  static char *type_s[] = {
    "char",
    "double"
    "float",
    "int",
    "void",
  };

  if (bsearch(&token, type_s, sizeof(type_s) / sizeof(char *),
              sizeof(char *), compare)) {
    return 1;
  }

  return 0;
}

int IsTypeQual(char *token) {
  static char *type_qual[] = {"const", "volatile"};

  if (bsearch(&token, type_qual, sizeof(type_qual) / sizeof(char *),
              sizeof(char *), compare)) {
    return 1;
  }

  return 0;
}
