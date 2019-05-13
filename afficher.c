#include<stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>

#include "afficher.h"

void afficher(SDL_Surface *surface,char *nom){
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture, *tmp = NULL;
 
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
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
    surface = SDL_LoadBMP(nom);//chargement de l'image
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
