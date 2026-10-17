// week5_task3_student_management_system.c
// Name: Džoanna Šarlote  Surname: Akselrode  Student ID: 251RDC072
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// TODO: Implement the functions to load, save, add, and list students.
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int  load_students(Student arr[], int max);          // returns number of records loaded
int  save_students(const Student arr[], int count);  // 0 on success, -1 on error
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int  read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    Student students[MAX_STUDENTS];
    char input[LINE_LEN];
    int count;
    int choice;
    char *end;

    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

    do {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        if (read_line("Select an option: ", input, sizeof(input)) != 0) {
            choice = 3; // input ended, so just save and quit
        } else {
            choice = (int)strtol(input, &end, 10);
            if (end == input || *end != '\0')
                choice = 0; // not a number
        }

        switch (choice) {
        case 1:
            list_students(students, count);
            break;
        case 2:
            add_student(students, &count);
            break;
        case 3:
            if (save_students(students, count) != 0)
                perror("Error saving " DATA_FILE);
            printf("Data saved. Goodbye!\n");
            break;
        default:
            printf("Invalid option. Try again.\n");
        }
    } while (choice != 3);

    return EXIT_SUCCESS;
}

// Provided helper – prints a prompt and reads one line from stdin into buf.
// The trailing newline is removed. Returns 0 on success, -1 on end of input (EOF).
int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }
    size_t len = strcspn(buf, "\r\n");
    if (buf[len] == '\0' && len == size - 1) {
        // Line was longer than the buffer: discard the rest of it.
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    buf[len] = '\0';
    return 0;
}

// reads lines like "name,id,gpa" from the file
int load_students(Student arr[], int max) {
    FILE *f = fopen(DATA_FILE, "r");
    char line[LINE_LEN];
    int n = 0;

    if (f == NULL)
        return 0; // no file yet = first run, nothing to load

    while (n < max && fgets(line, sizeof(line), f) != NULL) {
        // skip lines that don't have all 3 fields
        if (sscanf(line, "%49[^,],%d,%f", arr[n].name, &arr[n].id, &arr[n].gpa) == 3)
            n++;
    }

    fclose(f);
    return n;
}

int save_students(const Student arr[], int count) {
    FILE *f = fopen(DATA_FILE, "w");
    int i;

    if (f == NULL)
        return -1;

    for (i = 0; i < count; i++)
        fprintf(f, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);

    fclose(f);
    return 0;
}

void add_student(Student arr[], int *count) {
    char name[LINE_LEN], id_str[LINE_LEN], gpa_str[LINE_LEN];
    char *end;
    long id;
    float gpa;
    int ok = 1;

    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    if (read_line("Enter name: ", name, sizeof(name)) != 0) return;
    if (read_line("Enter ID: ", id_str, sizeof(id_str)) != 0) return;
    if (read_line("Enter GPA: ", gpa_str, sizeof(gpa_str)) != 0) return;

    // name can't be empty, too long, or have a comma (comma is used in the file)
    if (name[0] == '\0' || strlen(name) >= NAME_LEN || strchr(name, ',') != NULL)
        ok = 0;

    // if something is left after the number, it's not valid
    id = strtol(id_str, &end, 10);
    if (end == id_str || *end != '\0')
        ok = 0;

    gpa = strtof(gpa_str, &end);
    if (end == gpa_str || *end != '\0' || !(gpa >= 0.0f && gpa <= 4.0f))
        ok = 0;

    if (!ok) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    strcpy(arr[*count].name, name);
    arr[*count].id = (int)id;
    arr[*count].gpa = gpa;
    (*count)++;
    printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count) {
    int i;

    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    for (i = 0; i < count; i++)
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
}
