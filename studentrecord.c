#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

// Function to add student
void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    getchar(); // clear buffer

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; // remove newline

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student record saved successfully!\n");
}

// Function to display students
void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Stored Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\n-------------------------\n");
        printf("Roll  : %d\n", s.roll);
        printf("Name  : %s\n", s.name);
        printf("Marks : %.2f\n", s.marks);
    }

    fclose(fp);
}

// Function to search student
void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter roll number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nStudent Found!\n");
            printf("Name  : %s\n", s.name);
            printf("Marks : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found!\n");
    }

    fclose(fp);
}

// Main function
int main() {
    int choice;

    do {
        printf("\n===== Student Data Storage System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 4);

    return 0;
}