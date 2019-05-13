#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "afficher.h"

int main(int argc, char* argv[]){
	SDL_Surface *s = NULL;
	afficher(s,"lac_en_montagne.bmp");

	return 0;
}
