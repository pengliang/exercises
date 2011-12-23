#ifndef K_AND_R_ASSIGNMENTS_EXERCISE_4_3_GETOPT_H
#define K_AND_R_ASSIGNMENTS_EXERCISE_4_3_GETOPT_H

/* Gets the next operator or numeric operand
 *
 * @param[out] op array to store the operand string
 *                or a funtion name.
 * @return operator like '+', '-', '*', '/'... or
 *         '0' for a numeric operand,
 *         'f' for a function name stored in op.
 * */
int GetOpt(char op[]);

#endif // K_AND_R_ASSIGNMENTS_EXERCISE_4_3_GETOPT_H

