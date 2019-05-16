#include<stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "selection.h"

int main(int argc, char* argv[]){
	SDL_Surface *s = SDL_LoadBMP("lac_en_montagne.bmp");
	//SDL_Surface *s = IMG_Load("sapin.png");
	selectionner_image(s,0,0,200,200);

	return 0;
}
