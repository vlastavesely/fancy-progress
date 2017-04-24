#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <fancy-progress.h>

#define ROUNDS 150
#define STRINGS_COUNT 7

static const char *strings[] = {
	"Lorem ipsum dolor sit amet",
	"Consectetur adipiscing elit",
	"Vivamus faucibus sagittis dui, tincidunt rhoncus mi",
	"Fringilla sollicitudin. Donec eget sagittis",
	"Quam, vitae fringilla nisl",
	"Donec dolor justo, hendrerit sed accumsan id, sodales",
	"Eu odio"
};


int main(int argc, char **argv)
{
	int i, r;

	fancy_progress_start();

	// just echoes random strings and updates the progress bar
	srand(time(NULL));
	for (i = 0; i <= ROUNDS; i++) {
		r = rand() % STRINGS_COUNT;
		fprintf(stdout, "%s...\n", strings[r]);
		fancy_progress_step(((float) i / ROUNDS) * 100);
		usleep(50 * 1000);
	}

	sleep(1); // for effect

	fancy_progress_stop();

	return 0;
}
