#ifndef GOL_FUNCTIONS_H
#define GOL_FUNCTIONS_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "constants.h"

struct CellPopulation {
	char* cell_states_array;
	int size;
};

struct CellPopulation* init_cell_population();
void update_cell_population(struct CellPopulation* cell_population_p);

#endif // GOL_FUNCTIONS_H
