#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sauvegarde.h"

int main(int argc, char *argv[]){
    SDL_Surface *surface = NULL;
    char s[25];
    surface = SDL_LoadBMP("lac_en_montagne.bmp");
    //surface = IMG_Load("sapin.png");
    if (!surface){
	fprintf(stderr, "Echec de chargement du sprite : %s\n ", SDL_GetError());
	return EXIT_FAILURE;
    }
    printf("choisissez un nom pour le fichier\n");
    scanf("%s",s);
    //sauvegarder_image_BMP(surface,s);		
    sauvegarder_image_PNG(surface,s);
    SDL_FreeSurface (surface);
    
    return 0;
}
