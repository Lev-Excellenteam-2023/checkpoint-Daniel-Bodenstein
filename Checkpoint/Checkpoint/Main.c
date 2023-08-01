#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "School.h"

// Creates a new student node
struct Student* createStudent(const char* fName, const char* lName, long long int phone, int level, int class, int grades[NUM_OF_GRADES]) {

    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent) {
        strcpy(newStudent->firstName, fName);
        strcpy(newStudent->lastName, lName);
        newStudent->phone = phone;
        newStudent->level = level;
        newStudent->classroom = class;
        for (int i = 0; i < NUM_OF_GRADES; i++) {
            newStudent->grades[i] = grades[i];
        }
        newStudent->next = NULL;
    }
    return newStudent;
}

// Inserts a student to a linked list
void insertStudent(struct Student* student) {

    if (school[student->level - 1][student->classroom - 1].student == NULL) {
        student->next = NULL;
        school[student->level - 1][student->classroom - 1].student = student;
    }
    else {
        student->next = school[student->level - 1][student->classroom - 1].student;
        school[student->level - 1][student->classroom - 1].student = student;   
    }
}

void printStudentList() {

    for (int i = 0; i < NUM_OF_LEVELS; i++) {
        for (int j = 0; j < NUM_OF_CLASSES; j++) {
            struct Student* temp = school[i][j].student;

            while (temp != NULL) {
                printf("%s %s 0%llu %d %d %d %d %d %d %d %d %d %d %d %d \n", temp->firstName, temp->lastName,
                    temp->phone, temp->level, temp->classroom, temp->grades[0], temp->grades[1], temp->grades[2]
                    , temp->grades[3], temp->grades[4], temp->grades[5], temp->grades[6], temp->grades[7]
                    , temp->grades[8], temp->grades[9]);
                temp = temp->next;
            }
        }
    }
}

void freeStudentList() {
    for (int i = 0; i < NUM_OF_LEVELS; i++) {
        for (int j = 0; j < NUM_OF_CLASSES; j++) {
            struct Student* temp;
            while (school[i][j].student != NULL) {
                temp = school[i][j].student;
                school[i][j].student = school[i][j].student->next;
                free(temp);
            }
        }
    }
}

int schoolInit() {
    for (int i = 0; i < NUM_OF_LEVELS; i++) {
        for (int j = 0; j < NUM_OF_CLASSES; j++) {
            school[i][j].student = NULL;
        }
    }
}

int main() {
    FILE* file = fopen("students.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    char fName[MAX_SIZE_OF_NAME];
    char lName[MAX_SIZE_OF_NAME];
    long long int phone;
    int level;
    int class;
    int grades[NUM_OF_GRADES];

    schoolInit();

    while (fscanf(file, "%s %s %llu %d %d %d %d %d %d %d %d %d %d %d %d", fName, lName, &phone, &level, &class,
        &grades[0], &grades[1], &grades[2], &grades[3], &grades[4], &grades[5], &grades[6],
        &grades[7], &grades[8], &grades[9]) == 15) {
        struct Student* student = createStudent(fName, lName, phone, level, class, grades);
        if (student) {
            insertStudent(student);
        }
    }

    fclose(file);

    // Prints the linked list of students
    printf("List of Students:\n");
    printStudentList();

    // Free the memory used by the linked list of students
    freeStudentList();

    return 0;
}