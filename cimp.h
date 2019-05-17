#ifndef	CIMP_H
#define	CIMP_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_thread.h>
# include <math.h>
# include <unistd.h>

typedef struct {
    int i;
} ThreadData;

typedef struct Windows{
  SDL_Window *win;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_Surface *surface;
  struct Windows* next;
}Windows;

char	**ft_strsplit(char const *s, char c);
int 	initialize_readline(char **env1);
int	parse(char **ptr);
void open(char *img_path);
int rotation(char *name, char *tour);
void afficher();
int paint(char *name, int nuance);
SDL_Window *create_window(char *name, int width, int height);
SDL_Renderer *create_renderer(Windows* w);
SDL_Texture *create_texture(Windows* w);
int symetrie_verticale(char *image);
int symetrie_horizontale(char *image);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
int remplissage(char *name, SDL_Color couleur, int d);
int save(char *name, char *new);
int select_img(char *name, int x, int y, int h, int l);

Windows* windows;

#endif