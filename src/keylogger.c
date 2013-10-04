#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main() {
	printf("Starting keylogger\n");

	int piped[2];

	pipe(piped);

	pid_t pid = fork();

	if(pid == -1) {
		perror("Child couldn't be created\n");
		exit(1);
	}

	if(pid == 0) {
		close(piped[1]);
		char *watchdogName = "./build/watchdog.exe";

		char readPipe[10];
		sprintf(readPipe, "%d", piped[0]);

		char *args[3];
		args[0] = watchdogName;
		args[1] = readPipe;
		args[2] = NULL;

		execv(watchdogName, args);
	}
	else {
		printf("Padre (%d)\n", getpid());
		close(piped[0]);
		sleep(10);
		printf("Muriendo el padre\n");
	}
}