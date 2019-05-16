#include<stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>

#include "afficher.h"


int main(int argc, char *argv[]){
	SDL_Surface *s1 = NULL;
	afficher(s1,"lac_en_montagne.bmp");
	
	return 0;
}

