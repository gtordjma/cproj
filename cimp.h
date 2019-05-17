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
int	parse(char **ptr, Windows* windows);
void open(Windows *windows, char *img_path);

#endif