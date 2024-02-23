#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "file_pessoas"

typedef struct person {
    char name[200];
    int age;
} Person;

int add_person(char *name, int age);
int list_persons(int N);
int update_age(char *name, int age);