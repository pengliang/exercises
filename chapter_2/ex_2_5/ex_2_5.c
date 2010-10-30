// Return first location in s1 where any char from s2 occurs.
//
// @param s1, s1 string buff
// @param s2, s2 string buff
// @return first location in s1 where any char from s2 occurs.
int Any(char s1[], char s2[]) {
  int i = 0, j = 0;
  for (i = 0; s1[i] != '\0'; ++i) {
    for (j = 0; s2[j] != '\0; ++j) {
      if (s1[i] == s2[j])
        return i;
    }
  }
  return -1;
}
