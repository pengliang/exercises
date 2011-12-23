#include "parse_declaration.h"
#include "main.h"

enum ParseState {
  // type qualifier
  kTypeQual,
  // type specifier
  kTypeSpec,
  // declarator
  kDeclarator,
  // direct declearator
  kDirDecl,
  // indentifier
  kIdentifier
};

void ParseDeclaration(char *type_qual, char *type_spec,
                      char *var_name, char *desc) {
  int type;
  char token[kMaxToken];

  ParseDeclarationSpec(type_qual, type_spec);

  do {
    ParseDeclarator(var_name, desc);
    PrintDesc(type_qual, type_spec, var_name, desc);
  } while ((type = GetToken(token)) == ',');

  if (type == ';') {
    return;
  } else {
    Error("Error: missing ; at the end");
  }
}

