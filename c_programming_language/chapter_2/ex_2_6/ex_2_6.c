// Sets n bits of x at position p with bits of y
//
// @param x
// @param p
// @param n
// @param y
unsigned SetBits(unsigned x, int p, int n, unsigned y) {
  return x & ~(~(~0 << n) << (p + 1 - n)) |
        (y & ~(~0 << n)) << (p + 1 - n);
}
