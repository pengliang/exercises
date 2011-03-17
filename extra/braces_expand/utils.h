#ifndef K_AND_R_ASSIGNMENTS_EXTRA_UTILS_H_
#define K_AND_R_ASSIGNMENTS_EXTRA_UTILS_H_

/* Reverses the string
 *
 * @param s input string
 * @param n size of the string
 * @return the pointer to the reversed string
 */
char *StringReverse(char *s, int n);

/* Convets the string s to integer value
 *
 * @param s string
 * @parame value[out]
 * @return 1 for successful complete, or
 *         0 for not valid string.
 */
int StrToInt(const char *s, int *value);

/* Converts the integer n to string s.
 * The buffer must have enough memory.
 *
 * @param n int value
 * @param s[out] output string
 * @return the pointer to the converted string
 */
char *IntToStr(int n, char *s);

/* Gets the substring of str
 *
 * @param str string
 * @param from sub string's starting index
 * @param to sub string's ending index
 */
char *SubStr(const char *str, int from, int to);

#endif // K_AND_R_ASSIGNMENTS_EXTRA_UTILS_H_

