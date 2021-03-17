#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include "ui.h"
#include "matrix.h"

#define ITERATIONS 300
#define REFRESH_DELAY 50000L

int main(int argc, char** argv) {
	printf("Hello matrix!\n");

	if (!init_ui()) {
		return EXIT_FAILURE;
	}

	matrix_init();

	for (int i = 0; i < ITERATIONS; ++i) {
		matrix_update();
		show_matrix();
		usleep(REFRESH_DELAY);
	}

	cleanup_ui();

	return 0;
}
