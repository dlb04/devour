/*
 * devour
 * X11 window swallower
 */

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

const char *prognam;

void 
run_command(char **argv) {
	pid_t p = fork();
	if (p == 0 && execvp(argv[1], argv + 1)){
		fprintf(stderr, "%s: error: %s\n", prognam, strerror(errno));
		exit(1);
	}
	wait(NULL);
}

void
usage(void){
	printf("Usage: \n\t%s COMMAND [OPTIONS]\n"
		"\t%s - Displays this help\n",
		prognam, prognam
		); exit(0);
}

int 
main(int argc, char **argv) {

	prognam = argv[0];
	if (argc == 1)
		usage();

	Window win;
	Display *dis = XOpenDisplay(NULL);
	XGetInputFocus(dis, &win, (int[]){1});
	XUnmapWindow(dis, win);
	XFlush(dis);
	run_command(argv);
	XMapWindow(dis, win);
	XCloseDisplay(dis);
	return 0;
}
