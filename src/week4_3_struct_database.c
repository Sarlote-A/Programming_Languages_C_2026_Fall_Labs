/*
 * week4_3_struct_database.c
 * Author: Džoanna Šarlote Akselrode
 * Student ID: 251RDC072
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Use malloc to allocate space for n Student records,
 *   read each record from the user, print them as a table,
 *   and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {
    int n, i;
    struct Student *list;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 1;
    }

    list = malloc(n * sizeof(struct Student));
    if (list == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter data for student %d: ", i + 1);
        /* %49s so a long name can't overflow name[50] */
        if (scanf("%49s %d %f", list[i].name, &list[i].id, &list[i].grade) != 3) {
            printf("Invalid input.\n");
            free(list);
            return 1;
        }
    }

    printf("\n");
    printf("%-6s %-11s %s\n", "ID", "Name", "Grade");
    for (i = 0; i < n; i++) {
        printf("%-6d %-11s %.1f\n", list[i].id, list[i].name, list[i].grade);
    }

    free(list);
    return 0;
}
