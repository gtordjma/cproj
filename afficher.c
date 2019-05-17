#include "cimp.h"

SDL_Window *create_window(char *name, int width, int height)
{
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE;
    SDL_Window *w = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if(!w)
    {
        fprintf(stderr, "Erreur creation window : %s\n", SDL_GetError());
        return NULL;
    }
    return w;
}

SDL_Renderer *create_renderer(Windows* w)
{
    SDL_Renderer *rend = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED);
    if (!rend)
    {
        fprintf(stderr, "echec de création du renderer : %s\n", SDL_GetError());
        return NULL;
    }
    return rend;
}

SDL_Texture *create_texture(Windows* w)
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(w->renderer, w->surface);
    if (!texture){
        fprintf(stderr, "Echec de création de la texture : %s\n", SDL_GetError());
        return NULL;
    }
    return texture;
}

SDL_Surface *create_surface(char *path)
{
    SDL_Surface *surface = IMG_Load(path);
    if (!surface)
    {
        fprintf(stderr, "Echec de chargement du sprite : %s \n", SDL_GetError());
        return NULL;
    }
    return surface;
}

int check_image(char *img)
{
    SDL_Surface *s = create_surface(img);
    if (s == NULL)
    {
        SDL_FreeSurface(s);
        return 0;
    }
    else
    {   
        SDL_FreeSurface(s);
        return 1;

    }
}

void afficher(Windows* w){
    SDL_SetWindowSize(w->win,w->surface->w,w->surface->h);
    SDL_Rect dest = {0, 0, w->surface->w, w->surface->h};
    SDL_RenderCopy(w->renderer, w->texture, NULL, &dest);
    SDL_RenderPresent(w->renderer);
}

void init_first_img(Windows *w, char *img_path)
{
    w = malloc(sizeof(Windows));

    Windows first;
    first.surface = create_surface(img_path);
    first.win = create_window("1", first.surface->w, first.surface->h);
    first.renderer = create_renderer(&first);
    first.texture = create_texture(&first);
    first.next = NULL;
    memcpy(w,&first,sizeof(Windows));
    afficher(&first);
    printf("%s est dans la window : %d\n", img_path, SDL_GetWindowID(first.win));
}

void open(Windows *windows, char *img_path)
{
    Windows* cursor = windows;
    if (check_image(img_path))
    {
        if (cursor == NULL)
            init_first_img(windows, img_path);
        else
        {
            while(cursor->next)
                cursor = cursor->next;
            cursor->next = malloc(sizeof(struct Windows));
            cursor = cursor->next;
            cursor->surface = create_surface(img_path);
            cursor->win = create_window(img_path, cursor->surface->w, cursor->surface->h);
            cursor->renderer = create_renderer(cursor);
            cursor->texture = create_texture(cursor);
            cursor->next = NULL;
            afficher(cursor);
            printf("%s est dans la window : %d\n", img_path, SDL_GetWindowID(cursor->win));
        }
    }
}