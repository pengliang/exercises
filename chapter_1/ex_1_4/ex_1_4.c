#include <stdio.h>

// print Celsius-Fahrenheit table for celsius=0,20,...,300;
int main() {
  int lower = 0;	// lower bound of temperature table
  int upper = 300;	// upper bound
  int step = 20;	// step size
  float fahr;
  float celsius = lower;

  printf("Fahr  Celsius\n");	// The title of table
  while (celsius <= upper) {
    fahr = (9.0 * celsius) / 5.0 + 32.0;
    printf("%3.0f   %6.1f\n", celsius, fahr);
    celsius += step;
  }
  return 0;
}

