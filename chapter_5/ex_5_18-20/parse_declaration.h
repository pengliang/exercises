#ifndef K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_DECLARATION_H
#define K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_DECLARATION_H

/* Parses the declaration grammar.
 *
 * The syntax of the declaration is:
 *
 *  declaration:
 *    declaration-specifier declarator-list
 *
 *  declaration-specifiers:
 *    opt type-qualifier type-specifier
 *
 *  type-specifier: one of
 *    void char int float double
 *
 *  type-qualifier: one of
 *    const volatile
 *
 *  declarator-list:
 *    declarator
 *    declarator-list, declartor
 *
 *  declarator:
 *    opt pointer direct-declarator
 *
 *  direct-declarator:
 *    identifier
 *    (declarator)
 *    director-declarator[opt size]
 *    director-declarator(opt parameter-list)
 *
 *  pointer:
 *    *
 *    * pointer
 *
 *  parameter-list:
 *    parameter-declaration
 *    parameter-list, parameter-declaration
 *
 *  parameter-declaration:
 *    declaration-specifiers declarator
 *    declaration-specifiers opt pointer
 *
 * @param type_qual[out] type qualifier part of declaration-specifier
 * @param type_spec[out] type specifier part of declaration-specifier
 * @param var_name[out] identifier part of declarator
 * @param desc[out] description for declarator
 */
void ParseDeclaration(char *type_qual, char *type_spec,
                      char *var_name, char *desc);

#endif // K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_DECL_H
