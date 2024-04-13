#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)

int main (int argc, char * argv[]){

	init_vector();
	print_vector();

	// Open the FIFO for reading
	int fd = mkfifo(SERVER, 0666);
	if (fd == -1) {
		perror("open");
		_exit(1);
	}

	// Read the message from the FIFO
	Msg msg;
	while (1) {
		int fd = open(SERVER, O_RDONLY);
		if (fd == -1) {
			perror("open");
			_exit(1);
		}
		
		if (read(fd, &msg, sizeof(Msg)) == -1) {
			perror("read");
			_exit(1);
		}
		printf("Received message: needle = %d, pid = %d\n", msg.needle, msg.pid);

		int count = count_needle(msg.needle);
		msg.occurrences = count;


		// Communicate with the client
		int fd_client = open(CLIENT, O_WRONLY);
		if (fd_client == -1) {
			perror("open");
			_exit(1);
		}

		if (write(fd_client, &msg, sizeof(Msg)) == -1) {
			perror("write");
			_exit(1);
		}

		close(fd_client);
		close(fd);
	}


	
	return 0;
}
