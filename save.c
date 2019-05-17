#include "cimp.h"

void sauvegarder_image_BMP(SDL_Surface *image, char* nom){
  SDL_SaveBMP(image, strcat(nom,".bmp"));
}

void sauvegarder_image_PNG(SDL_Surface *image, char* nom){
  IMG_SavePNG(image, strcat(nom,".png"));
}

int save(char *name, char *new)
{
  Windows *c = windows;
  while(c && c->win && ((int)SDL_GetWindowID(c->win) != atoi(name)))
    c = c->next;
  if (c == NULL)
    return 0;
  sauvegarder_image_BMP(c->surface, new);
  sauvegarder_image_PNG(c->surface, new);
  return 1;
}