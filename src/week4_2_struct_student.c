/*
 * week4_2_struct_student.c
 * Author: Džoanna Šarlote Akselrode
 * Student ID: 251RDC072
 * Description:
 *   Demonstrates defining and using a struct in C.
 *   Define a 'Student' struct with name, id and grade, create two
 *   instances with the values from the instructions, and print them.
 *
 *   This program reads no input. Output must match the format in the
 *   Week 4 instructions exactly (it is checked by the autograder).
 */

#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {
    struct Student a, b;

    /* can't assign a string to a char array with =, so use strcpy */
    strcpy(a.name, "Alice Johnson");
    a.id = 1001;
    a.grade = 9.1f;

    strcpy(b.name, "Bob Smith");
    b.id = 1002;
    b.grade = 8.7f;

    printf("Student 1: %s, ID: %d, Grade: %.1f\n", a.name, a.id, a.grade);
    printf("Student 2: %s, ID: %d, Grade: %.1f\n", b.name, b.id, b.grade);

    return 0;
}
