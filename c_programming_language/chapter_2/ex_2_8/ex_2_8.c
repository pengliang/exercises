// Rotate x to the right by n poistions.
unsigned RightRot(unsigned x, int n) {
  int rbit;
  while (n-- > 0) {
    rbit = (x & 1) << (sizeof(unsigned) - 1);
    // Shift x one position right.
    x >>= 1;
    // Complete one rotation
    x |= rbit;
  }
  return x;
}
