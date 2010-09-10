#include <stdio.h>

// print Fahrenheit-Celsius table for fahr=0,20,...,300;
int main() {
  int lower = 0;  // lower bound of temperature table
  int upper = 300;  // upper bound
  int step = 20;  // step size
  double fahr = lower;
  double celsius;

  printf("Fahr  Celsius\n");	// The title of table
  while (fahr <= upper) {
    celsius = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f   %6.1f\n", fahr, celsius);
    fahr += step;
  }
  return 0;
}

