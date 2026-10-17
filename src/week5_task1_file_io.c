// week5_task1_file_io.c
// Name: Džoanna Šarlote  Surname: Akselrode  Student ID: 251RDC072
//
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming
// TODO: Fill in the missing parts marked below.
//
// Build: make lab5   Run: ./bin/week5_task1_file_io

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_FILENAME "data.txt"
#define LINE_LEN 256

int main(int argc, char *argv[]) {
    FILE *f;
    const char *filename = DEFAULT_FILENAME;
    char line[LINE_LEN];
    int count = 0;

    // file name can also be given as an argument
    if (argc > 1)
        filename = argv[1];

    printf("Writing lines to %s...\n", filename);
    f = fopen(filename, "w");
    if (f == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    fprintf(f, "Hello, file I/O in C!\n");
    fprintf(f, "This is another line.\n");
    fclose(f); // close it so everything gets written

    // open again, this time for reading
    f = fopen(filename, "r");
    if (f == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    printf("Reading contents:\n");
    while (fgets(line, sizeof(line), f) != NULL) {
        printf("%s", line); // line already ends with \n
        count++;
    }
    fclose(f);

    printf("Lines read: %d\n", count);
    return EXIT_SUCCESS;
}
