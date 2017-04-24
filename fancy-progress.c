#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>

#include <fancy-progress.h>

static struct winsize w;
static int initialized = 0;

static void fancy_progress_init()
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	// Resizes a tty window in order to ignore last line
	// and clears output after the cursor.
	fprintf(stdout, "\n\0337\033[0;%dr\0338\033[1A\033[J", w.ws_row - 1);
	fflush(stdout);
}

static void fancy_progress_abort()
{
	fancy_progress_stop();
	exit(0);
}


void fancy_progress_start()
{
	signal(SIGWINCH, fancy_progress_init);
	signal(SIGINT, fancy_progress_abort);
	fancy_progress_init();
	initialized = 1;
	fancy_progress_step(0);
}

void fancy_progress_step(float progress)
{
	if (initialized == 0) {
		fprintf(stderr, "error: fancy_progress_step() called before fancy_progress_start().\n");
		exit(1);
	}
	char *bar = malloc(w.ws_col);

	int width = (w.ws_col - 20);
	memset(bar, '.', width);
	memset(bar, '#', (int)(width * (progress / 100)));
	bar[width] = 0;

	fprintf(stdout, "\e[s\e[%d;0H\e[42;30mProgress: [%3d%%]\e[0m [%s]\e[u", w.ws_row + 1, (int) progress, bar);
	fflush(stdout);

	free(bar);
}

void fancy_progress_stop()
{
	// Clears screen after cursor and restores original tty size.
	fprintf(stdout, "\033[J\n\0337\033[0;%dr\0338\033[1A", w.ws_row);
	fflush(stdout);
}
