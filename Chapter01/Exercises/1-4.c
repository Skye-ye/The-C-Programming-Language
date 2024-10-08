#include <stdio.h>

int main() {
  float fahr, celsius;
  float lower, upper, step;

  lower = 0;
  upper = 100;
  step = 5;

  printf("Celsius Fahrenheit\n");

  celsius = lower;
  while (celsius <= upper) {
    fahr = celsius * (9.0 / 5.0) + 32.0;
    printf("%7.0f %10.1f\n", celsius, fahr);
    celsius += step;
  }

  return 0;
}
