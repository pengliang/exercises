/* Reverses string s in place recursively */
void Reverse(char s[], int i, int len) {
  int temp, j;

  j = len - (i + 1);

  if (i < j) {
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    Reverse(s, ++i, len);
  }
}
