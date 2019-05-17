#include "cimp.h"

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	switch(bpp) {
	case 1:	
		*p = pixel;
		break;	

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		} else {
			p[0] = pixel & 0xff;			
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}

Uint32 getpixel(SDL_Surface *surface, int x, int y){
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	
	switch(bpp) {
	case 1:
		return *p;
		break;
		
	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
			return p[0] << 16 || p[1] << 8 || p[2];
		}else{
			return p[0] || p[1] << 8 || p[2] << 16;
		}
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		return 0;
	}
}

SDL_Surface *make_noir_et_blanc(SDL_Surface* img){
	Uint8 r,g,b;
	SDL_LockSurface(img);
	for(int i=0;i<img->w;i++){
		for(int j=0;j<img->h;j++){
			SDL_GetRGB(getpixel(img,i,j),img->format,&r,&g,&b);
			Uint8 m = (r+g+b)/3;
			Uint32 w = SDL_MapRGB(img->format,m,m,m);
			putpixel(img,i,j,w);
		}
	}
	SDL_UnlockSurface(img);
	return img;
}

int noir_et_blanc(char *name){

  SDL_Surface *new = NULL;
  SDL_Texture *t = NULL;
  Windows *c = windows;
  while(c && c->win && ((int)SDL_GetWindowID(c->win) != atoi(name)))
    c = c->next;
  if (c == NULL)
    return 0;
  new = make_noir_et_blanc(c->surface);
  c->surface = new;
  t = create_texture(c);
  c->texture = t;
  afficher(c);
  return 1;
}
