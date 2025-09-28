#include "sdl_functions.h"

bool init_visualizer(struct Gol* gol_p) {
	if (!SDL_Init(SDL_FLAGS)) {
		fprintf(stderr, "Error initializing SDL library: %s\n", SDL_GetError());
		return false;
	}
	printf("SDL library initalized !\n");

	gol_p->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (gol_p->window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error creating window: %s\n", SDL_GetError());
		return false;
	}

	gol_p->renderer = SDL_CreateRenderer(gol_p->window, NULL);
	if (gol_p->renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error creating renderer: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(gol_p->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	return true;
}

void clear_program(struct Gol* gol_p) {
	SDL_DestroyRenderer(gol_p->renderer);
	SDL_DestroyWindow(gol_p->window);
	SDL_Quit();
}

void draw_grid(struct Gol* gol_p) {
	SDL_SetRenderDrawColor(gol_p->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < N_CELLS+1; i++) {
		SDL_RenderLine(gol_p->renderer, 0, i*CELLS_SIZE, GRID_WIDTH, i*CELLS_SIZE);
		SDL_RenderLine(gol_p->renderer, i*CELLS_SIZE, 0, i*CELLS_SIZE, GRID_HEIGHT);
	}
	SDL_SetRenderDrawColor(gol_p->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void fill_grid(struct Gol* gol_p, struct CellPopulation* cell_population_p) {
	for (int i = 0; i < N_CELLS; i++) {
		for (int j = 0; j < N_CELLS; j++) {
			SDL_FRect cell = {i*CELLS_SIZE, j*CELLS_SIZE, CELLS_SIZE, CELLS_SIZE};
			if (cell_population_p->cell_states_array[i + N_CELLS*j] == ALIVE) SDL_SetRenderDrawColor(gol_p->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			else SDL_SetRenderDrawColor(gol_p->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(gol_p->renderer, &cell);
		}
	}
}
