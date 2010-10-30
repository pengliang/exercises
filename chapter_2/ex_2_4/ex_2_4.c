// Delete each char in s1 which is in s2.
//
// @param s1, s1 string buffer
// @param s2, s2 string buffer
void Squeeze(char s1[], char s2[]) {
  int i = 0, j = 0, k = 0;
  for (i = 0; s1[i] != '\0'; ++i) {
    for (j = 0; s2[j] != '\0' && s2[j] != s1[i]; ++j) {}
    if (s2[j] == '\0') {
      s1[k++] = s1[i];
    }
  }
  s1[k] = '\0';
}
