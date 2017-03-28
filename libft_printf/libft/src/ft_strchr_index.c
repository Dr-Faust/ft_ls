#include "libft.h"

int		ft_strchr_index(char *s, int c)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}
