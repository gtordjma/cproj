#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "afficher.h"
#include "pixel.h"

SDL_Surface * mise_en_gris(SDL_Surface* img,int n){
  SDL_PixelFormat *fmt = img -> format;
  Uint8 r, g, b, a;
  Uint8 m;
  int w = img -> w;
  int h = img -> h;
  for(int y =0; y < h;y++){
    for(int x = 0; x < w;x++){
      //printf("%d",c->r);
      Uint32 p = getpixel(img, x, y);
      SDL_GetRGBA(p, fmt, &r, &g, &b, &a);
      m = (r + g + b)/3;
      m = m - (n*m/100);
      p = SDL_MapRGBA(fmt, m, m, m, a);
      putpixel(img, x, y, p);
    }
  }
  SDL_UnlockSurface(img);
  return img;
}



int main(int argc, char* argv[]){
	SDL_Surface *image = NULL;
	SDL_Surface *image2 = NULL;
	SDL_Surface *p = NULL;

	p = SDL_LoadBMP("lac_en_montagne.bmp");
	image2 = mise_en_gris(p,80);
	//afficher(image,"");
	afficher(image2,"");
	while(1)
	{}
	return 0;
}
