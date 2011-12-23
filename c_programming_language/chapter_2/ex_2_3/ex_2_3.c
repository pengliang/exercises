// Converts hexadecimal string s to integer.
// The hex string may be prefixed with 0x or 0X.
//
// @param s hexadecimal string.
// @return the integer converted from hex string.
int HexStringToInt(char s[]) {
  // Decimal digit corresponding to current hex character.
  int hexdigit = 0;
  // Position of hex string.
  int pos = 0;
  // Integer converted from hex string, will be returned.
  int n = 0;
  // Hexadecimal digits flag, 1 for hex, 0 for other.
  int inhex = 1;
  // Skip the optional prefix.
  if(s[1] == 'x' || s[1] == 'X') {
    pos = 2;
  }

  while (inhex) {
    int c = s[pos++];
    if (c >= '0' && c <= '9') {
      hexdigit = c - '0';
    } else if (c >= 'a' && c <= 'f') {
      hexdigit = c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
      hexdigit = c - 'A' + 10;
    } else {
      inhex = 0;
    }
    if (inhex) {
      n = 16 * n + hexdigit;
    }
  }
  return n;
}

enum Paserstate {
  kStateOfHex,
  kStateOfOther
};

// DFA version, it looks weird.
int HexStringToIntByDFA(char s[]) {
  // Decimal digit corresponding to current hex character.
  int hexdigit = 0;
  // Position of hex string.
  int pos = 0;
  // Integer converted from hex string, will be returned.
  int n = 0;
  // Hexadecimal digits flag, 1 for hex, 0 for other.
  int inhex = 1;
  // Skip the optional prefix.
  enum PaserState state = kStateOfHex;

  if(s[1] == 'x' || s[1] == 'X') {
    pos = 2;
  }
  while((c = s[pos++]) != '\0') {
    switch (state) {
      case kStateOfHex:
        if (c >= '0' && c <= '9') {
          hexdigit = c - '0';
        } else if (c >= 'a' && c <= 'f') {
          hexdigit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
          hexdigit = c - 'A' + 10;
        } else {
          state = kStateOfOther;
        }
        n = 16 * n + hexdigit;
        break;
      case kStateOfOther:
        return n;
        break;
    }
  }
}
