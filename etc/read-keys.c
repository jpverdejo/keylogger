#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>

main() {
	int file;

	file = open("/dev/input/event2", O_RDONLY);
	struct input_event ev;

	while(1) {
		read(file, &ev, sizeof(struct input_event));
		if(ev.type == EV_KEY) {
			if(ev.value == 1) {
				printf(" : [key %i]\n", ev.code);
			}
		}
	}
}