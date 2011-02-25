/* Concatenates t to the end of s.
 * Assume the space was allocated enough.
 *
 * @param s
 * @param t
 */
void strcat(char *s, char *t) {
  while (*s) {
    s++;
  };
  while (*s++ = *t++);
}
