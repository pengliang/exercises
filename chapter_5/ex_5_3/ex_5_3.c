/* Appends the src string to the dest string,
 * overwriting the null byte ('\0') at the end of dest,
 * and then adds a terminating null byte.
 * The strings may not overlap, and the dest string
 * must have enough space for the result.
 *
 * @param dest string
 * @param src string
 * @return a pointer to the resulting string dest.
 */
char *strcat(char *dest, const char *src) {
  char *result = dest;
  while (*dest) {
    dest++;
  };
  while (*dest++ = *src++);
  return result;
}
