// week5_task4_struct_binary_io.c   (BONUS)
// Name: Džoanna Šarlote  Surname: Akselrode  Student ID: 251RDC072
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int  save_student_binary(const Student *s, const char *filename);  // 0 on success, -1 on error
int  load_student_binary(const char *filename, Student *out);      // 0 on success, -1 on error
long file_size(const char *filename);                              // bytes, -1 on error

int main(void) {
    Student s1 = {0}; // all zeros, so the rest of name isn't random bytes in the file
    Student loaded = {0};
    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";
    FILE *txt;

    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    printf("Saving student in binary format...\n");
    if (save_student_binary(&s1, bin_file) != 0) {
        perror(bin_file);
        return EXIT_FAILURE;
    }

    // also save as text to compare the sizes
    txt = fopen(txt_file, "w");
    if (txt == NULL) {
        perror(txt_file);
        return EXIT_FAILURE;
    }
    fprintf(txt, "%s %d %.2f\n", s1.name, s1.age, s1.gpa);
    fclose(txt);

    printf("Loading student from binary file...\n");
    if (load_student_binary(bin_file, &loaded) != 0) {
        perror(bin_file);
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    printf("Text file size: %ld bytes\n", file_size(txt_file));
    printf("Binary file size: %ld bytes\n", file_size(bin_file));
    return EXIT_SUCCESS;
}

int save_student_binary(const Student *s, const char *filename) {
    FILE *f = fopen(filename, "wb");
    size_t n;

    if (f == NULL)
        return -1;

    n = fwrite(s, sizeof(Student), 1, f); // writes the whole struct at once
    fclose(f);
    return (n == 1) ? 0 : -1;
}

int load_student_binary(const char *filename, Student *out) {
    FILE *f = fopen(filename, "rb");
    size_t n;

    if (f == NULL)
        return -1;

    n = fread(out, sizeof(Student), 1, f);
    fclose(f);
    return (n == 1) ? 0 : -1;
}

// go to the end of the file, the position there = size in bytes
long file_size(const char *filename) {
    FILE *f = fopen(filename, "rb");
    long size;

    if (f == NULL)
        return -1;

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return -1;
    }
    size = ftell(f);
    fclose(f);
    return size;
}
