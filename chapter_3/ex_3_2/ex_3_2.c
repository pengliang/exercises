// Expands newline and tab into visible sequences
// while copying the string s to t. 
// Note: source string s should be end of '\0'.
//
// @param s source string end of '\0'.
// @param t target string.
void Escape(char s[], char t[]) {
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

// Converts escape sequences into real characters
// while copying the string s to t.
//
// @param s source string end of '\0'
// @param t target string.
void Unescape(char s[], char t[]) {
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

// DFA version of unescape
void UnescapeByDFA(char s[], char t[]) {
  int i = 0, j = 0, c;
  enum PaserState {
    kNormal,
    kEscape
  } state = kNormal;

  while ((c = s[i++]) != '\0') {
    switch (state) {
      case kNormal:
        switch (c) {
          case '\\':
            state = kEscape;
            break;
          default:
            t[j++] = c;
        }
        break;
      case kEscape:
        switch (c) {
          case 'n':
            t[j++] = '\n';
            state = kNormal;
            break;
          case 't':
            t[j++] = '\t';
            state = kNormal;
            break;
          default:
            t[j++] = '\\';
            t[j++] = c;
            state = kNormal;
        }
        break;
    }
  }
  t[j] = '\0';
}
