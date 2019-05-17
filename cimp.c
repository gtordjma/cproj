#include "cimp.h"

void clean()
{
	Windows *tmp;
	Windows *tmp2;
	while (windows!=NULL)
	{
		tmp = windows;
		if (tmp->next)
		{
			tmp2 = tmp->next;
			while(tmp2->next)
			{
				tmp = tmp2;
				tmp2 = tmp2->next;
			}
			SDL_DestroyTexture(tmp2->texture);
    		SDL_FreeSurface (tmp2->surface);
    		SDL_DestroyRenderer(tmp2->renderer);
    		if (tmp2->win)
    			SDL_DestroyWindow(tmp2->win);
    		tmp->next = NULL;
		}
		else
		{
			SDL_DestroyTexture(tmp->texture);
    		SDL_FreeSurface (tmp->surface);
    		SDL_DestroyRenderer(tmp->renderer);
    		if (tmp->win)
    			SDL_DestroyWindow(tmp->win);
    		windows = NULL;
		}
	}
}

static int Thread(void *v)
{
	char *prompt;
	int i = 1;
	while (1)
	{
		prompt = readline("\033[1m\033[33m cimp> \033[0m");
		if (strlen(prompt) > 0)
		{
			char **ptr = ft_strsplit(prompt, ' ');
			i = parse(ptr);
		}
		if (i == 0)
		{
			clean();
			exit(0);
		}
		free(prompt);
	}
}

int	main(int ac, char **av, char **env)
{
	windows = NULL;
	SDL_Thread *thread;
	initialize_readline(env); //initialisation de readline
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());

    thread = SDL_CreateThread(Thread, "Thread", (void *)NULL);
	SDL_Event event;
	while (1)
	{
		while( SDL_PollEvent( &event ) != 0)
        {
            if (event.type == SDL_WINDOWEVENT) {
        		switch (event.window.event) {
        			case SDL_WINDOWEVENT_CLOSE:
        			    SDL_DestroyWindow(SDL_GetWindowFromID(event.window.windowID));
        			    break;
        			default:
            			break;
        		}
        	}
        	else{
        		break;
        	}
		}
	}
	return (0);
}