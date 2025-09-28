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

void draw_grid(struct Gol* gol_p, int n_cells) {
	SDL_SetRenderDrawColor(gol_p->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	const float cell_size = GRID_DIM/n_cells;
	for (int i = 0; i < n_cells+1; i++) {
		SDL_RenderLine(gol_p->renderer, 0, i*cell_size, GRID_WIDTH, i*cell_size);
		SDL_RenderLine(gol_p->renderer, i*cell_size, 0, i*cell_size, GRID_HEIGHT);
	}
	SDL_SetRenderDrawColor(gol_p->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}
