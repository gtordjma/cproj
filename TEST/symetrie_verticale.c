#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

int symetrie_verticale_image(SDL_Surface *image){
	SDL_Surface *surface = NULL ;
	SDL_Rect line1, line2 ;
	int i;
	
	line1.y = 0 ;
	line1.w = 1 ;

	line2.y = 0 ;
	line2.w = 1 ;

	//Création d'une surface vide de la taille de l'image à copier
	surface = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0, 0, 0, 0);
	for (i=0;i<surface->w;i++)
	{
		//On copie successivement un trait de l'image de départ qu'on recopie de l'autre coté de l'image d'arrivée
		line1.x = i;
		line1.h = surface->h;
		line2.x = surface->w - i - 1;
		line2.h = surface->h;
		SDL_BlitSurface(image, &line1, surface, &line2);
	}
	if(surface == NULL){
		return 0;
	}
	return 1;
}
