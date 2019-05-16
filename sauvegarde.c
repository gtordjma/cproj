#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sauvegarde.h"

void sauvegarder_image_BMP(SDL_Surface *image, char* nom){
  SDL_SaveBMP(image, strcat(nom,".bmp"));
}

void sauvegarder_image_PNG(SDL_Surface *image, char* nom){
  IMG_SavePNG(image, strcat(nom,".png"));
}
