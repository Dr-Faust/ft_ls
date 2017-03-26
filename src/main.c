#include "ft_ls.h"

int		main(int argc, char **argv)
{
	int		i;
	int		flags;

	if (!(i = ft_parse(argc, argv, &flags)))
		return (1);
	return (0);
}
