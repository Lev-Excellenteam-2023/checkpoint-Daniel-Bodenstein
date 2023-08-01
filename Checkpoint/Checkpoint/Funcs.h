#pragma once
#include "School.h"

struct Student* createStudent(const char* fName, const char* lName, long long int phone, int level, int class, int grades[NUM_OF_GRADES]);

void insertStudent(struct Student* student);

void printStudent(struct Student* student);

void printAllStudents();

void freeStudentList();

void schoolInit();

struct Student* getStudent(long long int phone, int level, int classroom);

void insertNewStudent();

void deleteStudent();

void editStudentGrade();

void searchStudent();

void moveMinToIndexZero(struct Student* topN[], int course);

void printTopNStudentsPerCourse();