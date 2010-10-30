// Expand shorthand notation in s1 into string s2.
//
// @param s1, string s1
// @param s2, string s2
void Expand(char s1[], char s2[]) {
  char c;
  int i = 0, j = 0;
  while ((c = s1[i++]) != '\0') {
    if (s1[i] == '-' && s1[i++] >= c) {
      ++i;
      while (c < s1[i]) {
        s2[j++] = c++;
      }
    } else {
      s2[j++] = c;
    }
  }
  s2[j] = '\0';
}
