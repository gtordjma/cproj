#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

SDL_Window *afficher(SDL_Surface *surface,char *nom);
SDL_Surface * rotation(SDL_Surface* img, char ** argv);

SDL_Window *afficher(SDL_Surface *surface,char *nom){
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture, *tmp = NULL;
 
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
    }
    atexit(SDL_Quit);
    	
    window = SDL_CreateWindow("Mon Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
 
    if(!window)
      {
	fprintf(stderr, "Erreur creation window : %s", SDL_GetError());
      }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
      {
	fprintf(stderr, "echec de création du renderer : %s", SDL_GetError());
      }
    if (!surface){
	fprintf(stderr, "Echec de chargement du sprite : %s ", SDL_GetError());
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture){
	    fprintf(stderr, "Echec de création de la texture : %s", SDL_GetError());
    }
    SDL_Rect dest = {0, 0, surface -> w, surface -> h};//un SDL_Rect qui sers de destination à l'image
    SDL_RenderCopy(renderer, texture, NULL, &dest); // copie de surface grâce au SDL_Renderer
    SDL_RenderPresent(renderer); //Affichage
    //SDL_Delay(3000);
    //SDL_DestroyTexture(texture);//fin de programme, destruction des entitées utilisées
    //SDL_FreeSurface (surface);
    //SDL_DestroyRenderer(renderer);
    return window;
}

SDL_Surface *rotation(SDL_Surface* surface, char ** argv){
	int ranges; int colonne; int nbTour;
	if (argv[1] == NULL || argv[2] != NULL){
    		perror("Erreur de syntaxe.\n");
    		return NULL;
  	}else{
      		nbTour = atoi(argv[1]);
  	}
  	if (surface == NULL){ 
    		printf("Pas d'image, veuillez importer une image\n");
    		return NULL;
  	}
  	nbTour = nbTour%4;
  // en fonction de la parité de la position
  	int new_largeur; 
  	int new_longueur;
  	if (nbTour % 2 != 0){
    		new_longueur = surface->h;
    		new_largeur = surface->w;
  	}else{
    		new_longueur = surface->w;
    		new_largeur = surface->h;
  	}
  //creation de la sdl surface final
  	SDL_Surface * image = SDL_CreateRGBSurface (surface->flags, new_longueur, new_largeur, surface->format->BitsPerPixel,
  surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

  	if (image == NULL){
    		printf("Echec de la creation de la RGB surface");
    		return NULL;
  	}
  	if(SDL_LockSurface(surface)!=0){
    		perror("Erreur lors de SDL_LockSurface dans rotation90degre");
    		perror(SDL_GetError());
    		return NULL;
  	}
  	if(SDL_LockSurface(image)!=0){
    		perror("Erreur lors de SDL_LockSurface dans rotation90degre");
    		perror(SDL_GetError());
    		return NULL;
  	}
  // nombre d'octet par pixel
  	int bpp = surface->format->BitsPerPixel / 8;
  	Uint8* initial_buf;
  	Uint8* final_buf;
  	switch (nbTour){
    	case 1: //rotation de 90 degrés
    		for (ranges = 0; ranges<surface->h; ranges++){
        		initial_buf = (Uint8*)(surface->pixels) + (ranges * surface->pitch);
        		final_buf = (Uint8*)(image->pixels) + (image->w - ranges -1) * bpp;
        		for (colonne = 0; colonne <surface->w; colonne ++){
          			memcpy(final_buf, initial_buf, bpp);
          			initial_buf += bpp;
          			final_buf += image -> pitch;
        		}
    		}
      		break;

    	case 2: //rotation de 180 degres
    		for (ranges = 0; ranges<surface->h; ranges++){
        		initial_buf = (Uint8*)(surface->pixels) + (ranges * surface->pitch);
        		final_buf = (Uint8*)(image->pixels) + ((image->h - ranges - 1) * image -> pitch) + (image->w - 1) * bpp;
        		for (colonne = 0; colonne <surface->w; colonne ++){
          			memcpy(final_buf, initial_buf, bpp);
          			initial_buf += bpp;
          			final_buf -= bpp;
        		}
    		}
    		break;
	
     	case 3: //rotation 270 degres
  		for (ranges = 0; ranges<surface->h; ranges++){
      			initial_buf = (Uint8*)(surface->pixels) + (ranges * surface->pitch);
		        final_buf = (Uint8*)(image->pixels) +  (ranges * bpp)+ (image -> h * image->pitch);
      			for (colonne = 0; colonne <surface->w; colonne ++){
        			memcpy(final_buf, initial_buf, bpp);
        			initial_buf += bpp;
        			final_buf -= image -> pitch;
      			}
  		}
  		break;
	
	default:
      		if (surface->pitch == image->pitch){ // si le pitch est le même (longueur d'une rangée en bits)
          		memcpy(image->pixels, surface->pixels, (surface->h * surface->pitch));
      		}else{
          		initial_buf = (Uint8*)(surface->pixels);
          		final_buf = (Uint8*)(image->pixels);
          		for (ranges = 0; ranges<surface->h; ranges++){
            			memcpy(final_buf, initial_buf, surface->w * bpp);
            			initial_buf += surface->pitch;
            			final_buf += image->pitch;
          		}
      		}
        	break;

   	}
  	SDL_UnlockSurface(surface);
  	SDL_UnlockSurface(image);

  	return image;
}

int main(int argc, char* argv[]){
	SDL_Surface *image = NULL;
	SDL_Surface *p = NULL;

	p = SDL_LoadBMP("lac_en_montagne.bmp");
	image = rotation(p,argv);
	afficher(image,"");
	while(1)
	{}
	return 0;
}

