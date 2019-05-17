#include "cimp.h"

int select_img(char *name, int x, int y, int h, int l){

	Windows *c = windows;
    while(c && c->win && ((int)SDL_GetWindowID(c->win) != atoi(name)))
      c = c->next;
    if (c == NULL)
      return 0;
	SDL_Rect rect = (SDL_Rect) {x, y, h, l};
	SDL_Window *window =
		SDL_CreateWindow("Ma selection", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Surface *win_surface = SDL_GetWindowSurface(window);
	if(SDL_BlitSurface(c->surface,&rect, win_surface, NULL)<0){
		fprintf(stderr, "echec de création du renderer : %s", SDL_GetError());
	}
	SDL_UpdateWindowSurface(window);
	return 1;
}