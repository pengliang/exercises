#include <stdio.h>

double celsius(double fahr);

// print Fahrenheit - Ceisius table for fahr = 0,20, ... ,300
int main() {
  int lower = 0;
  int upper = 300;
  int step = 20;
  double fahr = lower;

  while (fahr <= upper) {
    printf("%3.0f %6.1f\n", fahr, celsius(fahr));
    fahr += step;
  }
  return 0;
}

// convert fahr into celsius
double celsius(double fahr) {
  return (5.0 / 9.0) * (fahr - 32.0);
}
