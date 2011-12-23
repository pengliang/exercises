// Expand shorthand notation in s1 into string s2.
//
// @param s1, string s1
// @param s2, string s2
void Expand(char s1[], char s2[]) {
  char c;
  int i = 0, j = 0;
  while ((c = s1[i++]) != '\0') {
    if (s1[i] == '-' && s1[i+1] >= c) {
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

// DFA version
void ExpandByDFA(char s1[], char s2[]) {
  char c;
  int i = 0, j = 0, head_of_notation;
  enum PaserState {
    kStateOfNormal,
    kTailOfNotation
  } state;

  state = kStateOfNormal;

  while ((c = s1[i++]) != '\0') {
    switch (state) {
      case kStateOfNormal:
        switch (c) {
          case '-':
            head_of_notation = s2[j-1] + 1;
            state = kTailOfNotation;
            break;
          default:
            s2[j++] = c;
        }
        break;
      case kTailOfNotation:
        while (head_of_notation <= c) {
          s2[j++] = head_of_notation++;
        }
        state = kStateOfNormal;
        break;
    }
  }
  s2[j] = '\0';
}
