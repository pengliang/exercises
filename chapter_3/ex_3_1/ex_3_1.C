// Binary search algorithm, find x in v[0] <= v[1] <= v[2] <= ... <= v[n-1].
//
// @param x
// @param v, array address
// @param n, length of array.
// @return the index if x in array v, -1 if not.
int BinarySearch(int x, int v[], int n) {
  int low = 0, high = n -1;
  int mid = (mid + high) / 2;

  while (low <= high && x != v[mid]) {
    if (x < v[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
    mid = (low + high) / 2;
  }
  if (x == v[mid]) {
    // Found x in v.
    return mid;
  } else {
    // No match
    return -1;
  }
}
