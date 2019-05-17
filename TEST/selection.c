#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "afficher.h"

int selectionner_image(char *nom, int x, int y, int h, int l){
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	        fprintf(stderr,
                "\nImpossible d'initialiser SDL :  %s\n",
                SDL_GetError()
		);
        	exit(1);
    	}
    	atexit(SDL_Quit);
	SDL_Surface *surface = SDL_LoadBMP(nom);
	SDL_Rect rect = (SDL_Rect) {x, y, h, l};
	SDL_Window *window =
		SDL_CreateWindow("Mon Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Surface *win_surface = SDL_GetWindowSurface(window);
	if(SDL_BlitSurface(surface,&rect, win_surface, NULL)<0){
		fprintf(stderr, "echec de création du renderer : %s", SDL_GetError());
		return 0;
	}
	SDL_UpdateWindowSurface(window);
	//char c = getchar();
	SDL_FreeSurface (surface);
	SDL_FreeSurface (win_surface);
    	SDL_DestroyWindow(window);

	return 1;
}

/*int main(int argc, char* argv[]){
	SDL_Surface *s = selectionner_image("lac_en_montagne.bmp",0,100,200,200);
	afficher(s);

	return 0;
}*/





