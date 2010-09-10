#include <stdio.h>

// print Fahrenheit-Celsius table for Fahrenheit=0,20,...,300;
int main() {
  for (int fahr = 300; fahr >= 0; fahr -= 20) {
    printf("%3d  %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
  }
  return 0;
}

