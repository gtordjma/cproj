#include "cimp.h"
//ft_strsplit transforme un char * en char ** en coupant le char * pas le char c
static int		ft_count_word(char const *s, char c)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != c)
			{
				i++;
				if (s[i] == '\0')
					return (j);
			}
		}
		while (s[i] == c)
			i++;
	}
	return (j);
}

static int		strlenchar(const char *s, char c)
{
	int			i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static char		**ft_fill_in_array(char **array, char const *s, char c, int j)
{
	int			i;
	int			k;
	int			b;
	int			z;

	i = 0;
	k = -1;
	while (i < j)
	{
		b = -1;
		while (s[++k] == c)
			;
		z = strlenchar(&(s[k]), c);
		if (!(array[i] = (char *)malloc(sizeof(char) * strlenchar(&(s[k]), c))))
			return (NULL);
		while (++b < z)
		{
			array[i][b] = s[k];
			++k;
		}
		array[i][b] = '\0';
		i++;
	}
	array[i] = NULL;
	return (array);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**array;
	int			j;

	if (!s)
	{
		array = NULL;
		return (array);
	}
	j = ft_count_word(s, c);
	array = (char **)malloc(sizeof(char *) * (j + 1));
	if (!array)
		return (NULL);
	return ((char **)ft_fill_in_array(array, s, c, j));
}