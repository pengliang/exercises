#include "parse_declarator.h"
#include <string.h>
#include "get_token.h"
#include "parse_declaration_spec.h"
#include "main.h"

/* Parses direct declarator grammar, gets the identifier part
 * and describes the direct declarator.
 *
 * Its syntax is:
 *
 *  direct-declarator:
 *    identifier
 *    (declarator)
 *    director-declarator[opt size]
 *    director-declarator(opt parameter-list)
 *
 * @param var_name[out] identifier part of direct declarator
 * @param desc[out] description for the direct declarator
 */
static void ParseDirDeclarator(char *var_name, char *desc);

void ParseDeclarator(char *var_name, char *desc) {
  int pointer_num = 0;
  int i = 0, type = 0;
  char token[kMaxToken];

  while ((type = GetToken(token)) == '*') {
    ++pointer_num;
  }

  ungets(token);
  ParseDirDeclarator(var_name, desc);

  for (i = 0; i < pointer_num; ++i) {
    strcat(desc, " pointer to");
  }

  return;
}

enum ParseState {
  kDirDecl,
  kRightParen,
  kIdentifier,
  kParamRightParen
};

static void ParseDirDeclarator(char *var_name, char *desc) {
  int token_type;
  char token[kMaxToken];
  enum ParseState state = kDirDecl;

  memset(token, 0, kMaxToken);

  while ((token_type = GetToken(token)) != -1) {
    switch (state) {
      case kDirDecl:
        switch (token_type) {
          case '(':
            // Pattern is (declartor)
            ParseDeclarator(var_name, desc);
            state = kRightParen;
            break;
          case kName:
            // Pattern is identifier
            if (IsTypeSpec(token)) {
              Error("too many type specifier");
            } else {
              strcpy(var_name, token);
            }
            state = kIdentifier;
            break;
          default:
            ungets(token);
            return;
        }
        break;
      case kRightParen:
        if (token_type != ')') {
          Error("missing ) at the end of direct declarator");
        }
        state = kIdentifier;
        break;
      case kIdentifier:
        switch (token_type) {
          case kParens:
            // Pattern is identifier()
            strcat(desc, " function returning");
            return;
          case kBrackets:
            // Pattern is identifier[opt size]
            strcat(desc, " array");
            strcat(desc, token);
            strcat(desc, " of");
            return;
          case '(':
            // Pattern is identifier(opt param-list)
            strcat(desc, " function expecting");
            ParseParamList(desc);
            strcat(desc, " and returning");
            state = kParamRightParen;
            break;
          default:
            ungets(token);
            return;
        }
        break;
      case kParamRightParen:
        if (token_type != ')') {
          Error("missing ) at the end of parameter list");
        }
        return;
    }
  }
}
