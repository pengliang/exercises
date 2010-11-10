// Inverts the n bits of x that begin at position p
//
// @param x unsigned
// @param p position in x.
// @param n length of bits will be inverted.
unsigned Invert(unsigned x, int p, int n) {
  return x ^ (~(~0 << n) << (p + 1 -n));
}


