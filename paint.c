#include "cimp.h"

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
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


SDL_Surface *make_paint(SDL_Surface* img, int n){
	Uint8 r,g,b,a;
	SDL_Surface *surface = SDL_CreateRGBSurface(0, img->w, img->h, 32, 0, 0, 0, 0);
	for(int i=0;i<img->w;i++){
		for(int j=0;j<img->h;j++){
			SDL_GetRGBA(getpixel(img,i,j),img->format,&r,&g,&b,&a);
			Uint8 m = (r+g+b)/3;
			m = m - (n*m/100);
			Uint32 w = SDL_MapRGB(img->format,m,m,m);
			if (n == -1)
				w = SDL_MapRGBA(img->format, 255-r,255-g,255-b, 255-a);
			putpixel(surface,i,j,w);
		}
	}
	return surface;
}

int paint(char *name, int nuance){
    SDL_Surface *new = NULL;
    SDL_Texture *t = NULL;
    Windows *c = windows;
    while(c && c->win && ((int)SDL_GetWindowID(c->win) != atoi(name)))
      c = c->next;
    if (c == NULL)
      return 0;
    new = make_paint(c->surface, nuance);
    c->surface = new;
    t = create_texture(c);
    c->texture = t;
    afficher(c);
    return 1;
}
