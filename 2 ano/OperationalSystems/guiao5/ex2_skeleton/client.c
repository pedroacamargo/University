#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"

int main (int argc, char * argv[]){

	if (argc < 2) {
		printf("Missing argument.\n");
		_exit(1);
	}

	int fifo_client = mkfifo(CLIENT, 0666);
	if (fifo_client == -1) {
		perror("mkfifo");
		_exit(1);
	}

	Msg msg = {
		.needle = atoi(argv[1]),
		.pid = getpid(),
		.occurrences = 0
	};

	// Open the FIFO for writing
	int fd = open(SERVER, O_WRONLY);
	if (fd == -1) {
		perror("open");
		_exit(1);
	}

	// Write the message to the FIFO
	if (write(fd, &msg, sizeof(Msg)) == -1) {
		perror("write");
		_exit(1);
	}
	close(fd);


	// Open the FIFO for reading
	int fd_client = open(CLIENT, O_RDONLY);
	if (fd_client == -1) {
		perror("open");
		_exit(1);
	}

	// Read the message from the FIFO
	if (read(fd_client, &msg, sizeof(Msg)) == -1) {
		perror("read");
		_exit(1);
	}

	printf("Occurrences: %d\n", msg.occurrences);

	// close the fifo
	close(fd_client);
	unlink(CLIENT);


	return 0;
}

