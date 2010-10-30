// Count 1 bits in x
int BitCount(unsigned x) {
  int b = 0;
  for (; x != 0; x &= x - 1) {
    ++b;
  }
  return b;
}
