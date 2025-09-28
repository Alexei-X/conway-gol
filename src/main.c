#include "sdl_functions.h"

int main(int argc, char* argv[]) {

	struct Gol main_visualizer;
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
		draw_grid(&main_visualizer, 10);
		SDL_RenderPresent(main_visualizer.renderer);
	}

	clear_program(&main_visualizer);

	return 0;
}
