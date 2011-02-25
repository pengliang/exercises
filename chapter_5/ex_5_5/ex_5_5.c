/* Copys n characters from t to s
 *
 * @param s
 * @param t
 * @param n
 */
void strncpy(char *s, char *t, int n) {
  while (*t && n-- > 0) {
    *s++ = *t++;
  }
  while (n-- > 0) {
    *s++ = '\0';
  }
}

/* Concatenates n character of t to the end of s
 *
 * @param s
 * @param t
 * @param n
 */
void strncat(char *s, char *t, int n) {
  while (*s++);
  strncpy(--s, t, n);
}

/* Compares at most n characters of t with s
 *
 * @param s
 * @param t
 * @param n
 */
int strncmp(char *s, char *t, int n) {
  while (*s = *t) {
    if (*s == '\0' || --n <= 0) {
      return 0;
    }
    s++;
    t++;
  }
  return *s - *t;
}
