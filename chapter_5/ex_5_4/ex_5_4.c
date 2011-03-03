/* Checks if string t occurs at the end of string s
 *
 * @param s
 * @param t
 * @return 1 if t occurs at the end of s
 *         0 if not
 */
int strend(char *s, char *t) {
  // beginning of str s.
  char *bs = s;
  // beginning ot str t.
  char *bt = t;

  while (*s++);
  while (*t++);

  while (*--s == *--t) {
    if (t == bt || s == bs) {
      break;
    }
  }

  if (*s == *t && t == bt && *s != '\0') {
    return 1;
  } else {
    return 0;
  }
}
