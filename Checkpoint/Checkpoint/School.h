#pragma once
#include <stddef.h>
#include "Student.h"

struct Students school[NUM_OF_LEVELS][NUM_OF_CLASSES];

int schoolInit() {
	for (int i = 0; i < NUM_OF_LEVELS; i++) {
		for (int j = 0; j < NUM_OF_CLASSES; j++) {
			school[i][j].student = NULL;
		}
	}
}