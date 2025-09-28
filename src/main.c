#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include "constants.h"

#define SDL_FLAGS SDL_INIT_VIDEO

struct Visualizer {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

bool init_visualizer(struct Visualizer* visualizer_p);
void clear_program(struct Visualizer* visualizer_p);

int main(int argc, char* argv[]) {

	struct Visualizer main_visualizer;
	bool running = true;

	if (!init_visualizer(&main_visualizer)) {
		clear_program(&main_visualizer);
	}

	while (running) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}
		SDL_RenderClear(main_visualizer.renderer);
		SDL_RenderPresent(main_visualizer.renderer);
	}

	clear_program(&main_visualizer);

	return 0;
}

bool init_visualizer(struct Visualizer* visualizer_p) {
	if (!SDL_Init(SDL_FLAGS)) {
		fprintf(stderr, "Error initializing SDL library: %s\n", SDL_GetError());
		return false;
	}
	printf("SDL library initalized !\n");

	visualizer_p->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (visualizer_p->window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error creating window: %s\n", SDL_GetError());
		return false;
	}

	visualizer_p->renderer = SDL_CreateRenderer(visualizer_p->window, NULL);
	if (visualizer_p->renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error creating renderer: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(visualizer_p->renderer, 100, 50, 75, SDL_ALPHA_OPAQUE);

	return true;
}

void clear_program(struct Visualizer* visualizer_p) {
	SDL_DestroyRenderer(visualizer_p->renderer);
	SDL_DestroyWindow(visualizer_p->window);
	SDL_Quit();
}