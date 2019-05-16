#ifndef SAUVEGARDE_H_
#define SAUVEGARDE_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void sauvegarder_image_BMP(SDL_Surface *image, char* nom);
void sauvegarder_image_PNG(SDL_Surface *image, char* nom);


#endif
