#include <stdio.h>   // File I/O and printing
#include <string.h>  // String handling
#include <assert.h>  // Assertions for testing
#include "database.h"  // Database operations

void test_insert_student() {
    // Overwrite file to ensure a clean state
    FILE* file = fopen("students.csv", "w");
    fclose(file);

    // Insert a student
    Student student = {1, "Alice", 95.5};
    insert_student(student);

    // Read the file content
    file = fopen("students.csv", "r");
    assert(file != NULL);

    char line[256];
    fgets(line, sizeof(line), file);
    fclose(file);

    // Normalize line endings
    line[strcspn(line, "\r\n")] = 0; // Remove trailing '\r' or '\n'

    // Assert file content matches
    assert(strcmp(line, "1,Alice,95.50") == 0);

    printf("test_insert_student passed.\n");
}



void test_select_all_students() {
    // Prepare a test file
    FILE* file = fopen("students.csv", "w");
    fprintf(file, "1,Alice,95.50\n2,Bob,88.00\n");
    fclose(file);

    // Redirect stdout to a file
    freopen("output.txt", "w", stdout);
    select_all_students();
    freopen("/dev/tty", "w", stdout); // Restore stdout to terminal

    // Verify output
    file = fopen("output.txt", "r");
    assert(file != NULL);

    char line[256];
    fgets(line, sizeof(line), file);
    assert(strcmp(line, "ID, Name, Grade\n") == 0);

    fgets(line, sizeof(line), file);
    assert(strcmp(line, "1, Alice, 95.50\n") == 0);

    fclose(file);
    printf("test_select_all_students passed.\n");
}

void test_delete_student() {
    // Prepare a test file
    FILE* file = fopen("students.csv", "w");
    fprintf(file, "1,Alice,95.50\n2,Bob,88.00\n");
    fclose(file);

    // Delete a student
    delete_student(1);

    // Verify the file content
    file = fopen("students.csv", "r");
    assert(file != NULL);

    char line[256];
    fgets(line, sizeof(line), file);
    fclose(file);

    assert(strcmp(line, "2,Bob,88.00\n") == 0);
    printf("test_delete_student passed.\n");
}

int main() {
    test_insert_student();
    test_select_all_students();
    test_delete_student();

    printf("All tests passed!\n");
    return 0;
}
