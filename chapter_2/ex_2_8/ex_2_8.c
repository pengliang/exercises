// Compute the word length of the machine.
//
// @return the word length of the machine.
int WordLength(void) {
  int i = 0;
  unsigned v = (unsigned) ~0;
  for (i = 1; (v = v >> 1) > 0; ++i) {}
  return i;
}

// Rotate x to the right by n poistions.
unsigned RightRot(unsigned x, int n) {
  int rbit;
  while (n-- > 0) {
    rbit = (x & 1) << (WordLength() - 1);
    // Shift x one position right.
    x >>= 1;
    // Complete one rotation
    x |= rbit;
  }
  return x;
}
