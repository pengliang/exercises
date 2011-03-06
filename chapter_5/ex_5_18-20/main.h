#ifndef K_AND_R_ASSIGNMENTS_EX_5_20_MAIN_H
#define K_AND_R_ASSIGNMENTS_EX_5_20_MAIN_H

// Max length of one token
extern const int kMaxToken;

/* Prints the error message and exit
 *
 * @param msg message string
 */
inline void Error(const char *msg);

/* Pushes string s back to stream where it is available
 * for subsequent read operations.
 *
 * @param s string
 */
void ungets(const char *s);

/* Prints the description for declaration statement on stdout.
 *
 * @param type_qual type qualifier part of declaration, may be NULL
 * @param type_spec type specifier part of declaration
 * @param var_name identifier part of declaration
 * @param desc description for the declarator part of declaration.*/
void PrintDesc(char *type_qual, char *type_spec,
               char *var_name, char *desc);

#endif // K_AND_R_ASSIGNMENTS_EX_5_20_MAIN_H
