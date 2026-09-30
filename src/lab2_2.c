#include <stdio.h>

/*
    Task:
    Write a function `long long factorial(int n)` that computes n!
    using a loop (not recursion).

    In main():
      - Ask user for an integer n
      - If n is negative, print an error and exit
      - Otherwise, call factorial and print the result
*/

long long factorial(int n) {
  long long product = 1;

  while (n > 1) {
    product *= n;
    n--;
  }

  return product;
}

int main(void) {
  int n;

  printf("Enter a non-negative integer n: ");
  scanf("%d", &n);

  if (n < 0) {
    printf("Error: n must be non-negative.\n");
    return 1;
  }

  long long result = factorial(n);
  printf("%d! = %lld\n", n, result);

  return 0;
}
