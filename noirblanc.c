#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

void afficher(SDL_Surface *surface){//, char *nom){
	  SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture, *tmp = NULL;
  //  SDL_Surface *surface = NULL;
 
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
//return EXIT_FAILURE;
    }
    atexit(SDL_Quit);
    	
    window = SDL_CreateWindow("Mon Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
 
    if(!window)
      {
	fprintf(stderr, "Erreur creation window : %s", SDL_GetError());
//	return EXIT_FAILURE;
      }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
      {
	fprintf(stderr, "echec de création du renderer : %s", SDL_GetError());
//	return EXIT_FAILURE;
      }
  //  surface = SDL_LoadBMP(nom);//chargement de l'image
    if (!surface){
	fprintf(stderr, "Echec de chargement du sprite : %s ", SDL_GetError());
//	return EXIT_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture){
	    fprintf(stderr, "Echec de création de la texture : %s", SDL_GetError());
//	    return EXIT_FAILURE;
    }
    SDL_Rect dest = {0, 0, surface -> w, surface -> h};//un SDL_Rect qui sers de destination à l'image
    SDL_RenderCopy(renderer, texture, NULL, &dest); // copie de surface grâce au SDL_Renderer
    SDL_RenderPresent(renderer); //Affichage
    SDL_Delay(3000);
    SDL_DestroyTexture(texture);//fin de programme, destruction des entitées utilisées
    SDL_FreeSurface (surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


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


/*SDL_Surface * noir_et_blanc(SDL_Surface* img){
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
      //printf("%d",m);
      if(m<=127){
        p = SDL_MapRGBA(fmt,0,0,0, a);
      }else{
        p = SDL_MapRGBA(fmt,255,255,255, a);

      }
      putpixel(img, x, y, p);
    }
  }
  SDL_UnlockSurface(img);
  return img;
}*/

SDL_Surface * noir_et_blanc(SDL_Surface* img){
	//afficher(img);
	SDL_LockSurface(img);
	for(int i=0;i<img->w;i++){
		for(int j=0;j<img->h;j++){
			Uint8 r,g,b;
			SDL_GetRGB(getpixel(img,i,j),img->format,&r,&g,&b);
			Uint32 m = (r+g+b)/3;
			Uint32 w = SDL_MapRGB(img->format,m,m,m);
			putpixel(img,i,j,w);
		}
	}
	SDL_UnlockSurface(img);
	return img;
}


int main(int argc, char ** argv){
	SDL_Surface *surface = NULL;
	surface = SDL_LoadBMP("lac_en_montagne.bmp");
	SDL_Surface *s = NULL;
	s = noir_et_blanc(surface);
	afficher(s);
	
	return 0;

}
