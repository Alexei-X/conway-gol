#ifndef SDL_FUNCTIONS_H
#define SDL_FUNCTIONS_H

#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include "constants.h"

#define SDL_FLAGS SDL_INIT_VIDEO

// Game Of Life (gol) structure 
struct Gol {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

bool init_visualizer(struct Gol* gol_p);
void clear_program(struct Gol* gol_p);
void draw_grid(struct Gol* gol_p, int n_cells);

#endif // SDL_FUNCTIONS_H