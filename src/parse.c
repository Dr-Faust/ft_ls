#include "ft_ls.h"

static int	ft_parse_flags(char *s, int *flags)
{

}

int			ft_parse(int argc, char **argv, int *flags)
{
	int		i;

	i = 0;
	*flags = 0;
	while (++i < argc && argv[i][0] == '-' && argv[i][1])
	{
		if (argv[i][1] == '-' && argv[i][2])
			return (i + 1);
		if (!ft_parse_flags(argv[i], flags))
			return (0);
	}
	return (i);
}
