// Deletes each char in s1 which is in s2.
//
// @param s1 s1 string buffer
// @param s2 s2 string buffer
void Squeeze(char s1[], char s2[]) {
  int i = 0, j = 0, k = 0;
  while (s1[i++] != '\0') {
    while (s2[j] != s1[i])
      if (s2[j++] == '\0') {
        s1[k++] = s1[i];
      } else {
        break;
      }
  }
  s1[k] = '\0';
}
