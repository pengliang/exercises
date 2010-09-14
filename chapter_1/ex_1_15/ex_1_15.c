#include <stdio.h>

// Converts fahr into ceisius.
//
// @param fahr the fahrenheit value to convert.
// @return the ceisius value converted from param.
double FahrToCeisius(double fahr);

// prints Fahrenheit - Ceisius table for fahr = 0,20, ... ,300
int main() {
  int lower = 0;
  int upper = 300;
  int step = 20;
  double fahr = lower;

  while (fahr <= upper) {
    printf("%3.0f %6.1f\n", fahr, FahrToCeisius(fahr));
    fahr += step;
  }
  return 0;
}


double FahrToCeisius(double fahr) {
  return (5.0 / 9.0) * (fahr - 32.0);
}
