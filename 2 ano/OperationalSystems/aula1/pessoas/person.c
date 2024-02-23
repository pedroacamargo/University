#include "person.h"

// Add a person to a file
int add_person(char *name, int age) {
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    Person p;
    p.age = age;
    strcpy(p.name, name);

    ssize_t writtenBytes = write(fd, &p, sizeof(Person));
    if (writtenBytes == -1) {
        perror("write");
        return -1;
    }

    printf("Person added: %s, %d\n", name, age);


    close(fd);


    return 0;
}

int list_persons(int N) {

    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    int readPersons = 0;
    Person p;
    ssize_t bytesRead;; 
    // while we can read a person
    while (readPersons < N && (bytesRead = read(fd,&p,sizeof(p)))) {

        readPersons++;
        // write(1,&p,sizeof(Person));
        // if (bytesRead == -1) {
        //     perror("Failed");
        //     return -1;
        // }


        char buffer[260];
        int size = sprintf(buffer, "li a pessoa %s com a idade %d\n", p.name, p.age);
        write(1, buffer, size);


        // printf("Age: %d\n", p.age);
        // printf("Name: %s\n", p.name);
    }

    close(fd);

    return readPersons;
}

int update_age(char *name, int age) {

    // escrever a pessoa com a idade certa por cima da mesma pessoa com a idade errada
    
    return 0;
}