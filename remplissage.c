#include "cimp.h"

SDL_Surface *make_remplissage(SDL_Surface *img, SDL_Color *couleur, int d){
	SDL_PixelFormat *fmt = img -> format;
	Uint8 r, g, b, a;
	int w = img -> w;
  	int h = img -> h;
   	for(int y =0; y < h;y++){
    		for(int x = 0; x < w;x++){
      			Uint32 p = getpixel(img, x, y);
      			SDL_GetRGBA(p, fmt, &r, &g, &b, &a);
      			if((r-couleur->r)<=d && (g-couleur->g)<=d && (b-couleur->b)<=d)
      				p = SDL_MapRGBA(fmt, couleur->r, couleur->g,couleur->b, a);
      			putpixel(img, x, y, p);
      		}
    	}
  	SDL_UnlockSurface(img);
  	return img;
}

int remplissage(char *name, SDL_Color couleur, int d){
    SDL_Surface *new = NULL;
    SDL_Texture *t = NULL;
    Windows *c = windows;
    while(c && c->win && ((int)SDL_GetWindowID(c->win) != atoi(name)))
      c = c->next;
    if (c == NULL)
      return 0;
    new = make_remplissage(c->surface, &couleur, d);
    c->surface = new;
    t = create_texture(c);
    c->texture = t;
    afficher(c);
    return 1;
}