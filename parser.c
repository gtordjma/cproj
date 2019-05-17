#include "cimp.h"

int count_params(char** tab)
{
	int  i = 0;
	while(*tab)
	{
		tab++;
		i++;
	}
	return i;
}

int	parse(char **ptr)
{
	char **cursor = ptr;
	while (*cursor)
	{
		if (strcmp(*cursor, "open") == 0)
		{
			cursor++;
			while(cursor)
			{
				open(*cursor);
				cursor++;
				if (!*cursor)
					break;
			}
		}
		else if (strcmp(*cursor, "rotation") == 0)
		{
			cursor++;
			if (count_params(&(*cursor)) == 2)
				rotation(*cursor, *(cursor + 1));
		}
		else if (strcmp(*cursor, "save") == 0)
		{
			cursor++;
			if (count_params(&(*cursor)) == 2)
				save(*cursor, *(cursor + 1));
		}
		else if (strcmp(*cursor, "quit") == 0)
			return 0;
		else if (strcmp(*cursor, "remplissage") == 0){
			cursor++;
			if (count_params(&(*cursor)) == 4)
				remplissage(*cursor, (SDL_Color){atoi(*(cursor + 1)),atoi(*(cursor + 2)),atoi(*(cursor + 3))}, 255);	
		}
		else if (strcmp(*cursor, "remplacement") == 0){
			cursor++;
			if (count_params(&(*cursor)) == 5)
				remplissage(*cursor, (SDL_Color){atoi(*(cursor + 1)),atoi(*(cursor + 2)),atoi(*(cursor + 3))}, atoi(*(cursor + 4)));	
		}
		else if (strcmp(*cursor, "select") == 0){
			cursor++;
			if (count_params(&(*cursor)) == 5)
				select_img(*cursor, atoi(*(cursor + 1)), atoi(*(cursor + 2)), atoi(*(cursor + 3)), atoi(*(cursor + 4)));	
		}
		else if (strcmp(*cursor, "gris") == 0){
			cursor++;
			if (count_params(&(*cursor)) == 2)
				paint(*cursor, atoi(*(cursor + 1)));	
		}
		else if (strcmp(*cursor, "noirblanc") == 0){
			cursor++;
			if (count_params(&(*cursor)) == 1)
				paint(*cursor, 0);	
		}
		else if (strcmp(*cursor, "negatif") == 0){
			cursor++;
			if (count_params(&(*cursor)) == 1)
				paint(*cursor, -1);	
		}
		else if (strcmp(*cursor, "symetriehorizontale") == 0){
			cursor++;
			if (count_params(&(*cursor)) == 1)
				symetrie_horizontale(*cursor);	
		}
		else if (strcmp(*cursor, "symetrieverticale") == 0){
			cursor++;
			if (count_params(&(*cursor)) == 1)
				symetrie_verticale(*cursor);	
		}
		else{
			cursor++;
		}
	}
	return 1;
}