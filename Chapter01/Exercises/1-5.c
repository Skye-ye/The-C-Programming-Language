#include <stdio.h>

int main() {
  float fahr, celsius;

  printf("Fahrenheit Celsius\n");

  for (fahr = 300.0; fahr >= 0.0; fahr -= 20.0) {
    celsius = (5.0 / 9.0) * (fahr - 32);
    printf("%10.0f %7.1f\n", fahr, celsius);
  }

  return 0;
}
