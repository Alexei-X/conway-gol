#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>

#define SDL_FLAGS SDL_INIT_VIDEO

int main(int argc, char* argv[]) {

	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running = true;
	
	if (!SDL_Init(SDL_FLAGS)) {
		fprintf(stderr, "Error initializing SDL library: %s\n", SDL_GetError());
		return 1;
	}
	printf("SDL library initalized !\n");

	window = SDL_CreateWindow("AlgoVision", 800, 600, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error creating window: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error creating renderer: %s\n", SDL_GetError());
		return 1;
	}

	while (running) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
