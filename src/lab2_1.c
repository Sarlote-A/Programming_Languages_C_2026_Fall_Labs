#include <stdio.h>

/*
    Task:
    Write a function `int sum_to_n(int n)` that computes
    the sum of all integers from 1 up to n using a for loop.

    In main():
      - Ask user for a positive integer n
      - If n < 1, print an error
      - Otherwise, call sum_to_n and print the result
*/

int sum_to_n(int n) {
    // TODO: implement sum with a for loop
    // int a;
    int sum = 0;
    int b;
        for (int a=0; a<n; a++){
            printf("Enter the integer: ");
            scanf("%d", &b);
            sum = sum + b;
        }

    // printf(sum);

    return sum; // placeholder
}

int main(void) {
    int n; 
    int c;

    printf("Enter a positive integer n: ");
    scanf("%d", &n);
    while (n<1){
        printf("The value is too small. Enter the next value: ");
        scanf("%d", &n);
    }

    // TODO: validate input, call function, and print result
    c = sum_to_n(n);
    printf("The result of function is: ");
    printf("%d", c);

    return 0;
}
