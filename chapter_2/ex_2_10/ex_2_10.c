// Converts char c to lower case (ASCII ONLY)
//
// @param c may be the upper case character.
// @return the lower case of character.
int Lower(int c) {
  return c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;
}
