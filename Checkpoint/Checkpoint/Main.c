//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "School.h"
//#include "Funcs.h"
//

//int main() {
//    FILE* file = fopen("students_with_class.txt", "r");
//
//    if (file == NULL) {
//        printf("Error opening the file.\n");
//        return 1;
//    }
//
//    char fName[MAX_SIZE_OF_NAME];
//    char lName[MAX_SIZE_OF_NAME];
//    long long int phone;
//    int level;
//    int class;
//    int grades[NUM_OF_GRADES];
//
//    schoolInit();
//
//    while (fscanf(file, "%s %s %llu %d %d %d %d %d %d %d %d %d %d %d %d", fName, lName, &phone, &level, &class,
//        &grades[0], &grades[1], &grades[2], &grades[3], &grades[4], &grades[5], &grades[6],
//        &grades[7], &grades[8], &grades[9]) == 15) {
//        struct Student* student = createStudent(fName, lName, phone, level, class, grades);
//        if (student) {
//            insertStudent(student);
//        }
//    }
//
//    fclose(file);
//
//    // Prints the linked list of students
//    printf("List of Students:\n");
//    printAllStudents();
//
//    // Free the memory used by the linked list of students
//    freeStudentList();
//
//    return 0;
//}