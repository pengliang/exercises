#include <stdio.h>

// converts fahr into ceisius
double Ceisius(double fahr);

// prints Fahrenheit - Ceisius table for fahr = 0,20, ... ,300
int main() {
  int lower = 0;
  int upper = 300;
  int step = 20;
  double fahr = lower;

  while (fahr <= upper) {
    printf("%3.0f %6.1f\n", fahr, Ceisius(fahr));
    fahr += step;
  }
  return 0;
}

double Ceisius(double fahr) {
  return (5.0 / 9.0) * (fahr - 32.0);
}
