#include <stdio.h>
#include "mysystem.h"

void controller(int N, char** commands) {
	int status;
	int pids[N];
	pid_t res;


	for (int i = 0; i < N; i++) {
		res = fork();

		if(res == 0) {
			int count = 0;
			int ret;
			while((ret = mysystem(commands[i])) != 0) count++;
			_exit(ret);
		} else {
			pids[i] = res;
		}
	}


	for (int i = 0; i < N; i++) {
		int terminated = waitpid(pids[i], &status, 0);
		if (WIFEXITED(status)) {
			printf("Child %d (%s) terminated with status %d\n", terminated, commands[i], WEXITSTATUS(status));
		} else {
			printf("Child %d (%s) terminated abnormally\n", terminated, commands[i]);
		}
		// if (WIFEXITED(status)) {
		// 	printf("Child %d terminated with status %d\n", terminated, WEXITSTATUS(status));
		// }

	}
}

int main(int argc, char* argv[]) {

	char *commands[argc-1];
	int N = 0;
	for(int i=1; i < argc; i++){
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
		N++;
	}

	controller(N, commands);

	return 0;
}