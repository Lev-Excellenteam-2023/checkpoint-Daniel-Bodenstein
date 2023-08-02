#define NUM_OF_GRADES 10
#define NUM_OF_LEVELS 12
#define NUM_OF_CLASSES 10
#define MAX_SIZE_OF_NAME 50
#define MAX_GRADE 100
#define NUM_OF_TOP 10

struct Student {
    char firstName[MAX_SIZE_OF_NAME];
    char lastName[MAX_SIZE_OF_NAME];
    long long int phone;
    int level;
    int classroom;
    int grades[NUM_OF_GRADES];
    struct Student* next;
};

struct Students {
    struct Student* student;
};
