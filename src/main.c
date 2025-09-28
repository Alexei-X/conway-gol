#include "sdl_functions.h"
#include "gol_functions.h"
#include <unistd.h>

int main(int argc, char* argv[]) {

	struct Gol main_visualizer;
	bool running = true;

	if (!init_visualizer(&main_visualizer)) {
		clear_program(&main_visualizer);
	}

	struct CellPopulation* cell_population_p = init_cell_population();
	while (running) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}
		SDL_RenderClear(main_visualizer.renderer);
		fill_grid(&main_visualizer, cell_population_p);
		draw_grid(&main_visualizer);
		SDL_RenderPresent(main_visualizer.renderer);
		update_cell_population(cell_population_p);
		usleep(TICK*1000);
	}

	clear_program(&main_visualizer);
	free(cell_population_p->cell_states_array);
	free(cell_population_p);

	return 0;
}
