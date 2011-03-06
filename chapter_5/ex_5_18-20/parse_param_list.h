#ifndef K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_PARAM_LIST_H
#define K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_PARAM_LIST_H

/* Parses the parameter list
 *
 * Its syntax is:
 *
 * parameter-list:
 *   parameter-declaration
 *   parameter-list, parameter-declaration
 *
 * parameter-declaration:
 *   declaration-specifiers declarator
 *   declaration-specifiers opt pointer
 *
 * @param desc description for the parameter list
 * */
void ParseParamList(char *desc);

#endif // K_AND_R_ASSIGNMENTS_EX_5_20_PARSE_PARAM_LIST_H

