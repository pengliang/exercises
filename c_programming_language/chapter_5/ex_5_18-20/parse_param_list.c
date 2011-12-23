#include "parse_param_list.h"
#include <string.h>
#include "main.h"
#include "parse_declaration_spec.h"

static void ParseParamDecl(char *desc);

void ParseParamList(char *desc) {
  int type;
  char token[kMaxToken];

  do {
    ParseParamDecl(desc);
    type = GetToken(token);

    if (type == ',') {
      strcat(desc, ",");
    } else {
      break;
    }
  } while (1);

  // out of param list
  ungets(token);
}

/* Parses the parameter declaration grammar
 *
 * Its syntax is:
 *
 * parameter-declaration:
 *  declaration-specifiers declarator
 *  declaration-specifiers opt pointer
 *
 * @param desc description for the parameter declaration
 * */
static void ParseParamDecl(char *desc) {
  char type_qual[kMaxToken];
  char type_spec[kMaxToken];
  char var_name[kMaxToken];

  memset(type_qual, 0, kMaxToken);
  memset(type_spec, 0, kMaxToken);
  memset(var_name, 0, kMaxToken);

  ParseDeclarationSpec(type_qual, type_spec);

  ParseDeclarator(var_name, desc);

  if (*type_qual != '\0') {
    strcat(desc, " ");
    strcat(desc, type_qual);
  }
  strcat(desc, " ");
  strcat(desc, type_spec);
}
