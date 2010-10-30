// Expand newline and tab into visible sequences
// while copying the string s to t. '
// Note: source string s should be end of '\0'.
//
// @param s, source string end of '\0'.
// @param t, target string.
void escape(char s[], char t[]) {
  int i = 0, j = 0, c;

  while ((c = s[i++]) != '\0') {
    switch(c) {
      case '\n':
       t[j++] = '\\';
       t[j++] = 'n';
       break;
     case '\t':
       t[j++] = '\\';
       t[j++] = 't';
       break;
     default:
       t[j++] = c;
     }
  }
  t[j] = '\0';
}

// Convert escape sequences into real characters
// while copying the string s to t.
//
// @param s, source string end of '\0'
// @param t, target string.
void unescape(char s[], char []) {
  int i = 0, j = 0, c;

  while ((c = s[i++]) != '\0') {
    if (c != '\\') {
      t[j++] = c;
    } else {
      switch (c) {
        case 'n':
          t[j++] = '\n';
          break;
        case 't':
          t[j++] = '\t';
          break;
        default:
          t[j++] = '\\';
          t[j++] = c;
      }
    }
  }
  t[j] = '\0';
}
