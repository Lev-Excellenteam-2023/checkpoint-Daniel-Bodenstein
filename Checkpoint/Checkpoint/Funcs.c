#define _CRT_SECURE_NO_WARNINGS
#include "School.h"
#include "Funcs.h"
#include <stdio.h>
#include <stdlib.h>

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

void printStudent(struct Student* student) {
    printf("%s %s 0%llu %d %d %d %d %d %d %d %d %d %d %d %d \n", student->firstName, student->lastName,
        student->phone, student->level, student->classroom, student->grades[0], student->grades[1], student->grades[2]
        , student->grades[3], student->grades[4], student->grades[5], student->grades[6], student->grades[7]
        , student->grades[8], student->grades[9]);
}

void printAllStudents() {

    for (int i = 0; i < NUM_OF_LEVELS; i++) {
        for (int j = 0; j < NUM_OF_CLASSES; j++) {
            struct Student* temp = school[i][j].student;

            while (temp != NULL) {
                printStudent(temp);
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

void schoolInit() {
    for (int i = 0; i < NUM_OF_LEVELS; i++) {
        for (int j = 0; j < NUM_OF_CLASSES; j++) {
            school[i][j].student = NULL;
        }
    }
}

void insertNewStudent() {
    struct Student* student = (struct Student*)malloc(sizeof(struct Student));

    printf("Enter first name: ");
    scanf("%s", student->firstName);

    printf("Enter last name: ");
    scanf("%s", student->lastName);

    printf("Enter phone number: ");
    scanf("%llu", &student->phone);

    printf("Enter level: ");
    scanf("%d", &student->level);
    while (student->level < 1 || student->level > NUM_OF_LEVELS) {
        printf("Invalid input!\nLevel is between 1-%d \nEnter level: ", NUM_OF_LEVELS);
        scanf("%d", &student->level);
    }

    printf("Enter class: ");
    scanf("%d", &student->classroom);
    while (student->classroom < 1 || student->classroom > NUM_OF_CLASSES) {
        printf("Invalid input!\nClass is between 1-%d \nEnter class: ", NUM_OF_CLASSES);
        scanf("%d", &student->classroom);
    }

    printf("Enter %d grades: ", NUM_OF_GRADES);
    for (int i = 0; i < NUM_OF_GRADES; i++) {
        scanf("%d", &student->grades[i]);
        while (student->grades[i] < 0 || student->grades[i] > MAX_GRADE) {
            printf("Invalid input!\nGrades are between 0-%d \nEnter grades: ", MAX_GRADE);
            scanf("%d", &student->grades[i]);
        }
    }

    insertStudent(student);
    printAllStudents();
}

void deleteStudent() {
    long long int phone;
    int level;
    int classroom;

    printf("Enter phone number: ");
    scanf("%llu", &phone);

    printf("Enter level: ");
    scanf("%d", &level);
    while (level < 1 || level > NUM_OF_LEVELS) {
        printf("Invalid input!\nLevel is between 1-%d \nEnter level: ", NUM_OF_LEVELS);
        scanf("%d", &level);
    }

    printf("Enter class: ");
    scanf("%d", &classroom);
    while (classroom < 1 || classroom > NUM_OF_CLASSES) {
        printf("Invalid input!\nClass is between 1-%d \nEnter class: ", NUM_OF_CLASSES);
        scanf("%d", &classroom);
    }

    struct Student* previous = NULL;
    struct Student* current = school[level - 1][classroom - 1].student;
    if (current->phone == phone) {
        if (!(current->next)) {
            free(current);
            school[level - 1][classroom - 1].student = NULL;
        }
        else {
            school[level - 1][classroom - 1].student = current->next;
            free(current);
        }
    }
    else {
        while (current && current->phone != phone) {
            previous = current;
            current = current->next;
        }
        if (current && current->phone == phone) {
            free(current);
            previous->next = current->next;
        }
        else {
            printf("The student not found\n");
        }
    }

    printAllStudents();

}

 //  Return a student by phone, level and class
 //  or NULL if the student not found
struct Student* getStudent(long long int phone, int level, int classroom) {

    struct Student* current = school[level - 1][classroom - 1].student;

    while (current != NULL && current->phone != phone) {
        current = current->next;
    }
    if (!current)
    {
        printf("Student not found\n");
        return NULL;
    }
    else
        return current;
}

void editStudentGrade() {
    long long int phone;
    int level;
    int classroom;
    int subject;
    int grade;
    struct Student* student = NULL;

    do {
        printf("Enter phone number: ");
        scanf("%llu", &phone);

        printf("Enter level: ");
        scanf("%d", &level);
        while (level < 1 || level > NUM_OF_LEVELS) {
            printf("Invalid input!\nLevel is between 1-%d \nEnter level: ", NUM_OF_LEVELS);
            scanf("%d", &level);
        }

        printf("Enter class: ");
        scanf("%d", &classroom);
        while (classroom < 1 || classroom > NUM_OF_CLASSES) {
            printf("Invalid input!\nClass is between 1-%d \nEnter class: ", NUM_OF_CLASSES);
            scanf("%d", &classroom);
        }

        student = getStudent(phone, level, classroom);

    } while (!student);

    printf("Enter subject: ");
    scanf("%d", &subject);
    while (subject < 0 || subject > NUM_OF_GRADES) {
        printf("Invalid input!\nSubject is between 0-%d \nEnter class: ", NUM_OF_GRADES);
        scanf("%d", &subject);
    }

    printf("Enter grade: ");
    scanf("%d", &grade);
    while (grade < 0 || grade > MAX_GRADE) {
        printf("Invalid input!\nClass is between 0-%d \nEnter class: ", MAX_GRADE);
        scanf("%d", &grade);
    }

    student->grades[subject] = grade;

    printAllStudents();
}

void searchStudent() {

    char firstName[MAX_SIZE_OF_NAME];
    char lastName[MAX_SIZE_OF_NAME];

    printf("Enter first name: ");
    scanf("%s", firstName);

    printf("Enter last name: ");
    scanf("%s", lastName);

    for (int i = 0; i < NUM_OF_LEVELS; i++) {
        for (int j = 0; j < NUM_OF_CLASSES; j++) {
            struct Student* temp = school[i][j].student;

            while (temp != NULL) {
                if (!(strcmp(temp->firstName, firstName)) && !(strcmp(temp->lastName, lastName))) {
                    printStudent(temp);
                }
                temp = temp->next;
                
            }
        }
    }
}

void moveMinToIndexZero(struct Student* topN[], int course) {

    // Find the index of the minimum value of course in the array
    int minIndex = 0;
    for (int i = 1; i < NUM_OF_TOP; i++) {
        if (topN[i]->grades[course] < topN[minIndex]->grades[course]) {
            minIndex = i;
        }
    }

    struct Student* temp = &topN[0];
    topN[0] = topN[minIndex];
    topN[minIndex] = temp;
}

void printTopNStudentsPerCourse() {

    int level;
    int course;
    struct Student* topN[NUM_OF_TOP];

    printf("Enter level: ");
    scanf("%d", &level);
    while (level < 1 || level > NUM_OF_LEVELS) {
        printf("Invalid input!\nLevel is between 1-%d \nEnter level: ", NUM_OF_LEVELS);
        scanf("%d", &level);
    }

    printf("Enter course: ");
    scanf("%d", &course);
    while (course < 1 || course > NUM_OF_GRADES) {
        printf("Invalid input!\nLevel is between 1-%d \nEnter level: ", NUM_OF_GRADES);
        scanf("%d", &course);
    }

    struct Student* temp = NULL;
    int i = 0, j = 0;
    while (j < NUM_OF_TOP && i < NUM_OF_CLASSES) {
        temp = school[level - 1][i++].student;
        while (temp && j < NUM_OF_TOP) {
            topN[j++] = temp;
            temp = temp->next;
        }
    }
    i--;

    if (j == NUM_OF_TOP) {
        moveMinToIndexZero(topN, course);
        while (i < NUM_OF_CLASSES) {
            while (temp) {
                if (temp->grades[course] > topN[0]->grades[course]) {
                    topN[0] = temp;
                    moveMinToIndexZero(topN, course);
                }
                temp = temp->next;
            }
        }
    }

    for (int k = 0; k < j; k++) {
        printStudent(topN[k]);
    }
}