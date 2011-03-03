/* copies at most n bytes pointed to by src,
 * including the terminating null byte ('\0'),
 * to the buffer pointed to by dest.
 * Warning: If there is no null byte among the first n bytes of src,
 *          the string placed in dest will not be null-terminated.
 *
 * @param dest string
 * @param src string
 * @param n
 * @return a pointer to the destination string dest.
 */
char *strncpy(char *dest, const char *src, int n) {
  char *result = dest;
  while (*src && n-- > 0) {
    *dest++ = *src++;
  }
  while (n-- > 0) {
    *dest++ = '\0';
  }
  return result;
}

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

/* Appends at most n bytes from the src string to the string dest.
 * Overwriting the null byte ('\0') at the end of dest, and then
 * adds a terminating null byte.
 * The dest string must have enough space for the result.
 * The size of dest must be at leat strlen(dest) + n + 1;
 *
 * @param dest
 * @param src
 * @param n
 * @return a pointer to the resulting string dest.
 */
char *strncat(char *dest, const char *src, int n) {
  char *result = dest;
  while (*dest++);
  while (*src && n-- > 0) {
    *dest++ = *src++;
  }
  *dest++ = '\0';
  return result;
}

/* Compares the first n characters of two strings s1 and s2.
 *
 * @param s1 string
 * @param s2 string
 * @param n
 * @return an integer less than, equal to or greater than zero
 *         if the first n bytes of s1 are found to be less than,
 *         to match, or be greater than the first n bytes of s2.
 */
int strncmp(const char *s1, const char *s2, int n) {
  while (*s1 == *s2) {
    if (*s1 == '\0' || --n <= 0) {
      return 0;
    }
    s1++;
    s2++;
  }
  return *s1 - *s2;
}
