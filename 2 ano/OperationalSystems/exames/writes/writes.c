#include "writes.h"

int writes(char *filename, int bytes) {
    
    int fdInput = open("input.txt", O_RDONLY, 0644);
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    // Check if the file was opened successfully

    ssize_t bytesRead;
    char buffer[bytes];
    while (bytesRead = read(fdInput, buffer, sizeof(buffer))) {
        if (bytesRead == -1) {
            perror("Failed to read from stdin");
            return 1;
        }

        printf("Bytes read: %ld\n", bytesRead);
        size_t bytesWritten = write(fd, buffer, 16000); 
        printf("Bytes written: %ld\n", bytesWritten);

        while (bytesWritten < bytesRead) {
            size_t bytesWritten = write(fd, buffer + bytesRead, bytes);

            if (bytesWritten == -1) {
                perror("Failed to write to file");
                return 1;
            }

            printf("Bytes written: %ld\n", bytesWritten);

            bytesRead += bytesWritten;
        }
    }


    return 1;
}