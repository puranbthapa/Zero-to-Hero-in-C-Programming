#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();

void main() {
    int choice;

    while (1) {
        clrscr();
        printf("===== Student Record Management System =====\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Delete Student Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n"); getch();
        }
    }
}

void addStudent() {
    FILE *fp;
    struct Student s;
    fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!");
        getch();
        return;
    }

    printf("Enter Roll No: ");
    scanf("%d", &s.roll);
    fflush(stdin);
    printf("Enter Name: ");
    gets(s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student record added successfully!\n");
    getch();
}

void displayStudents() {
    FILE *fp;
    struct Student s;
    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found.\n");
        getch();
        return;
    }

    printf("\nRoll\tName\t\tMarks\n");
    printf("=====================================\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%-15s%.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    getch();
}

void searchStudent() {
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("File not found.\n");
        getch();
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nRecord Found!\n");
            printf("Roll: %d\n", s.roll);
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No record with roll number %d found.\n", roll);

    fclose(fp);
    getch();
}

void deleteStudent() {
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file.");
        getch();
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Record deleted successfully.\n");
    else
        printf("Record not found.\n");

    getch();
}
