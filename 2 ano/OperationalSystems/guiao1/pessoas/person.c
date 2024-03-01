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
        perror("Error writing to file");
        return -1;
    }

    long pos = lseek(fd, -sizeof(Person), SEEK_CUR); // SEEK_END -> end of file
    printf("Person added: %s, %d\n", name, age);


    close(fd);


    return pos/sizeof(Person);
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
    while (readPersons < N && (bytesRead = read(fd,&p,sizeof(p))) > 0) {

        readPersons++;

        char buffer[260];
        int size = sprintf(buffer, "li a pessoa %s com a idade %d\n", p.name, p.age); // sprintf -> pega na string, e escreve para o buffer
        write(1, buffer, size);


        // printf("Age: %d\n", p.age);
        // printf("Name: %s\n", p.name);
    }

    close(fd);

    return readPersons;
}

int update_age(char *name, int age) {

    int fd = open(FILENAME, O_RDWR);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    Person p;

    // while we can read a person
    while (read(fd,&p,sizeof(p)) > 0) {
        if (strcmp(p.name, name) == 0) {
            p.age = age;
            lseek(fd, -sizeof(Person), SEEK_CUR);
            write(fd, &p, sizeof(Person));
            printf("%s updated to %d\n", name, age);
            break;
        }
    }

    close(fd);

    return 1;
}

int update_age_v2(int i, int age) {
    Person p;

    int fd = open(FILENAME, O_RDWR);
    if (fd == -1) {
        perror("open");
        return -1;
    }


    int pos = lseek(fd, i*sizeof(Person), SEEK_CUR);
    if (pos == -1) {
        perror("lseek");
        return -1;
    }
    printf("Pos: %d\n", pos);

    ssize_t read_bytes = read(fd, &p, sizeof(Person));
    if (read_bytes == -1) {
        perror("read");
        return -1;
    }
    printf("Read %s with %d years old\n", p.name, p.age);
    
    pos = lseek(fd, -sizeof(Person), SEEK_CUR);
    if (pos == -1) {
        perror("lseek");
        return -1;
    }

    printf("Pos: %d\n", pos);

    p.age = age;
    write(fd, &p, sizeof(Person));

    close(fd);

    return 1;
}