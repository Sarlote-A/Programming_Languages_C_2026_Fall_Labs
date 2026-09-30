#include <stdio.h>

/*
    Task:
    Write a function `int is_prime(int n)` that returns 1 if n is prime,
    0 otherwise.

    In main():
      - Ask user for an integer n (>= 2)
      - If invalid, print an error
      - Otherwise, print all prime numbers up to n
*/

int is_prime(int n) {
  int d = 2;

  if (n <= 1) return 0;

  while (d * d <= n) {
    if ((n % d) == 0) return 0;
    d++;
  }

  return 1;
}

int main(void) {
  int n;
  int x;

  printf("Enter an integer n (>= 2): ");
  scanf("%d", &n);

  if (!(n >= 2)) {
    printf("Error: n must be >= 2.\n");
    return 0;
  }

  printf("Primes up to %d:", n);
  for (x = 2; x <= n; x++) {
    if (is_prime(x) == 1) printf(" %d", x);
  }
  printf("\n");

  return 0;
}
