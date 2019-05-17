#include "cimp.h"

SDL_Surface *symetrie_horizontale_image(SDL_Surface *image){
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
	return surface;
}

int symetrie_horizontale(char *name)
{
  SDL_Surface *new = NULL;
  SDL_Texture *t = NULL;
  Windows *c = windows;
  while(c && c->win && ((int)SDL_GetWindowID(c->win) != atoi(name)))
    c = c->next;
  if (c == NULL)
    return 0;
  new = symetrie_horizontale_image(c->surface);
  c->surface = new;
  t = create_texture(c);
  c->texture = t;
  afficher(c);
  return 1;
}