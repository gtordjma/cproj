#include "symetrie.h"

void symetrie_horizontal_image(){
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	 fprintf(stderr,
 "\nImpossible d'initialiser SDL : %s\n",
 SDL_GetError()
		);
 	exit(1);
 	}
 	atexit(SDL_Quit);

	SDL_Surface *image = SDL_LoadBMP("lac_en_montagne.bmp");
	SDL_Surface *surface = NULL ;
	SDL_Rect line1, line2 ;
	int i;
	
	line1.x = 0 ;
	line1.h = 1 ;

	line2.x = 0 ;
	line2.h = 1 ;

	//Création d'une surface vide de la taille de l'image à copier
	surface = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0, 0, 0, 0);
	for (i=0;i<surface->w;i++)
	{
		//On copie successivement un trait de l'image de départ qu'on recopie de l'autre coté de l'image d'arrivée
		line1.y = i;
		line1.w = surface->w;
		line2.y = surface->h - i - 1;
		line2.w = surface->w;
		SDL_BlitSurface(image, &line1, surface, &line2);
	}
	SDL_Window *window =
		SDL_CreateWindow("Mon Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, image->w, image->h, SDL_WINDOW_SHOWN);
	SDL_Surface *win_surface = SDL_GetWindowSurface(window);
	SDL_BlitSurface(surface, NULL, win_surface, NULL);

	SDL_UpdateWindowSurface(window);
	char c = getchar();
	SDL_FreeSurface (surface);
	SDL_FreeSurface (win_surface);
 	SDL_DestroyWindow(window);
}