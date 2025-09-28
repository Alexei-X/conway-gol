#include "gol_functions.h"

struct CellPopulation* init_cell_population() {
	srand(time(NULL));
	struct CellPopulation* cell_population_p = (struct CellPopulation*) malloc(sizeof(struct CellPopulation));
	if (cell_population_p == NULL) {
		fprintf(stderr, "Error allocating memory for CellPopulation");
		return NULL;
	}
	cell_population_p->size = GRID_CELLS_AREA;
	cell_population_p->cell_states_array = (char*) malloc(GRID_CELLS_AREA*sizeof(char));
	if (cell_population_p->cell_states_array == NULL) {
		fprintf(stderr, "Error allocating memory for cell states array");
		return NULL;
	}
	for (int i = 0; i < GRID_CELLS_AREA; i++) cell_population_p->cell_states_array[i] = rand()%2;

	return cell_population_p;
}

void update_cell_population(struct CellPopulation* cell_population_p) {
	srand(time(NULL));
	for (int i = 0; i < GRID_CELLS_AREA; i++) cell_population_p->cell_states_array[i] = rand()%2;
}
