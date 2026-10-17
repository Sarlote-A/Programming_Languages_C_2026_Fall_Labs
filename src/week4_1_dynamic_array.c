/*
 * week4_1_dynamic_array.c
 * Author: Džoanna Šarlote Akselrode
 * Student ID: 251RDC072
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, i;
    int *numbers;
    long sum = 0;
    double avg;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    /* we only know n at runtime so the array has to be allocated */
    numbers = malloc(n * sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            printf("Invalid input.\n");
            free(numbers); /* don't leak memory on error */
            return 1;
        }
        sum += numbers[i];
    }

    /* cast to double, otherwise 7 and 8 would give 7.00 */
    avg = (double)sum / n;

    printf("Sum = %ld\n", sum);
    printf("Average = %.2f\n", avg);

    free(numbers);
    return 0;
}
