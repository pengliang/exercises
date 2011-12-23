#ifndef K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_DECLARATOR_H
#define K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_DECLARATOR_H

/* Parses declarator grammar, gets the identifier part and
 * describes the declarator.
 *
 * Its snytax is:
 *
 *  declarator:
 *    opt pointer direct-declarator
 *
 *  pointer:
 *    *
 *    * pointer
 *
 *  direct-declarator:
 *    identifier
 *    (declarator)
 *    director-declarator[opt size]
 *    director-declarator(opt parameter-list)
 *
 * @param var_name[out] identifier part of direct_declarator
 * @param desc[out] description for declarator
 */
void ParseDeclarator(char *var_name, char *desc);

#endif // K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_DECLARATOR_H

