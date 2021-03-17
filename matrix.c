#include <assert.h>
#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ui.h"

#define NUM_DRIPS 250

#define PROB_DRIP_SPAWN 0.65
#define PROB_DIM 0.55
#define PROB_CHANGE 0.95

// #define RANDOM_PRINTABLE_CHARACTER 'X'
#define RANDOM_PRINTABLE_CHARACTER (33 + (rand() % 80))

typedef struct {
	int x, y;
	bool live;
	bool bright;
} drip;

cell matrix[MAXX][MAXY];
drip drips[NUM_DRIPS];

double rand01() {
	return (double) rand() / (double) RAND_MAX;
}

void init_drips() {
	for (int i = 0; i < NUM_DRIPS; ++i) {
		drips[i].live = false;
	}
}

void matrix_init() {

	for (int x = 0; x < MAXX; ++x) {
		for (int y = 0; y < MAXY; ++y) {
			matrix[x][y].char_value = 0;
			matrix[x][y].intensity = 0;
		}
	}

	init_drips();
}

void fade_n_change_matrix() {
	for (int x = 0; x < MAXX; ++x) {
		for (int y = 0; y < MAXY; ++y) {
			// randomly change characters -- even invisible ones
			if (rand01() < PROB_CHANGE || matrix[x][y].char_value == 0) {
				matrix[x][y].char_value = RANDOM_PRINTABLE_CHARACTER;
			}

			if (rand01() < PROB_DIM && matrix[x][y].intensity > 0) {
				matrix[x][y].intensity--;
			}
		}
	}
}

void try_add_drips() {
	for (int i = 0; i < NUM_DRIPS; ++i) {
		if (drips[i].live == false) {
			drips[i].live = true;
			drips[i].x = rand() % MAXX;
			drips[i].y = 0;
			drips[i].bright = rand() % 2;
			return; // TODO try without this 'return'
		}
	}
}

void update_drips() {
	for (int i = 0; i < NUM_DRIPS; ++i) {
		if (drips[i].live) {
			if (drips[i].bright) {
				matrix[drips[i].x][drips[i].y].intensity = MAX_INTENSITY;
			} else {
				matrix[drips[i].x][drips[i].y].intensity = MIN_INTENSITY;
			}

			if (++drips[i].y >= MAXY - 1) {
				drips[i].live = false;
			}
		}
	}
}

void matrix_update() {
	if (rand01() < PROB_DRIP_SPAWN) {
		try_add_drips();
	}

	update_drips();

	fade_n_change_matrix();
}
