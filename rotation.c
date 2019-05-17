#include "cimp.h"

SDL_Surface *make_rotation(SDL_Surface* surface, int n)
{
	int ranges;
  int colonne;
	int nbTour = n%4;
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

int rotation(char *name, char *tour)
{
  SDL_Surface *new = NULL;
  SDL_Texture *t = NULL;
  Windows *c = windows;
  while(c && c->win && ((int)SDL_GetWindowID(c->win) != atoi(name)))
    c = c->next;
  if (c == NULL)
    return 0;
  new = make_rotation(c->surface, atoi(tour));
  c->surface = new;
  t = create_texture(c);
  c->texture = t;
  afficher(c);
  return 1;
}