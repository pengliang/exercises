#ifndef K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_DECLARATION_SPEC_H
#define K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_DECLARATION_SPEC_H

/* Parses the declaration specifier grammar, gets the type
 * qualifier part and type specifier part.
 *
 * Its syntax is:
 *
 * declaration-specifier:
 *   opt type-qualifier type-specifier
 *
 * type-qualifier: one of
 *   const volatile
 *
 * type-specifier: one of
 *   void char int float double
 *
 * @param type_qual[out] type qualifier part of declaration,
 *                       may be NULL
 * @param type_spec[out] type specifier part of declaration
 */
void ParseDeclarationSpec(char *type_qual, char *type_spec);

/* Checks a token is valid type specifier or not.
 *
 * @param token string buffer
 * @return 0 for the token string is not valid type specifier
 *         1 for the token string is valid type specifier
 */
int IsTypeSpec(char *token);

/* Checks a token is valid type qualifier or not.
 *
 * @param token string buffer
 * @return 0 for the token string is not valid type qualifier
 *         1 for the token string is valid type qualifier
 */
int IsTypeQual(char *token);

#endif // K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_DECLARATION_SPEC_H
