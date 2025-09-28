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
	char* new_states_array = (char*) malloc(GRID_CELLS_AREA*sizeof(char));
	for (int i = 0; i < N_CELLS; i++) {
		for (int j = 0; j < N_CELLS; j++) {
			int n_alive = 0;
			for (int dj = -1; dj <= 1; dj++) {
			    for (int di = -1; di <= 1; di++) {
			        if (dj == 0 && di == 0) continue;
			        int j_neighbor = (j + dj + N_CELLS) % N_CELLS;
			        int i_neighbor = (i + di + N_CELLS) % N_CELLS;
			        n_alive += cell_population_p->cell_states_array[j_neighbor * N_CELLS + i_neighbor];
			    }
			}
			if (cell_population_p->cell_states_array[N_CELLS*j + i] == ALIVE) {
			    if (n_alive < 2 || n_alive > 3) {
			        new_states_array[N_CELLS*j + i] = DEAD;
			    } else if (n_alive == 2 || n_alive == 3) {
			        new_states_array[N_CELLS*j + i] = ALIVE;
			    }
			} else {
			    if (n_alive == 3) {
			        new_states_array[N_CELLS*j + i] = ALIVE;
			    } else {
			        new_states_array[N_CELLS*j + i] = DEAD;
			    }
			}
		}
	}
	for (int k = 0; k < GRID_CELLS_AREA; k++) cell_population_p->cell_states_array[k] = new_states_array[k];
	free(new_states_array);
}
