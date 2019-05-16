#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "selection.h"

void selectionner_image(SDL_Surface *surface, int x, int y, int h, int l){
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	        fprintf(stderr,
                "\nImpossible d'initialiser SDL :  %s\n",
                SDL_GetError()
		);
        	exit(1);
    	}
    	atexit(SDL_Quit);
	SDL_Rect rect = (SDL_Rect) {x, y, h, l};
	SDL_Window *window =
		SDL_CreateWindow("Mon Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Surface *win_surface = SDL_GetWindowSurface(window);
	if(SDL_BlitSurface(surface,&rect, win_surface, NULL)<0){
		fprintf(stderr, "echec de création du renderer : %s", SDL_GetError());
	}
	SDL_UpdateWindowSurface(window);
	char c = getchar();
	SDL_FreeSurface (surface);
	SDL_FreeSurface (win_surface);
    	SDL_DestroyWindow(window);

	//return surface;
}
