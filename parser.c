#include "cimp.h"

int	parse(char **ptr, Windows* windows)
{
	char **cursor = ptr;
	while (*cursor)
	{
		if (strcmp(*cursor, "open") == 0)
		{
			cursor++;
			while(cursor)
			{
				open(windows, *cursor);
				cursor++;
				if (!*cursor)
					break;
			}
		}
		else if (strcmp(*cursor, "quit") == 0)
		{

			return 0;
		}else{
			cursor++;
		}
	}
	return 1;
}