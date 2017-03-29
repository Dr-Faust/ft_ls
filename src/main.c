/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:45:45 by opodolia          #+#    #+#             */
/*   Updated: 2017/03/29 21:35:09 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_error(char *str, int error)
{
	if (error == USAGE)
	{
		ft_printf("ft_ls: illegal option -- %c\n", *str);
		ft_printf("usage: ft_ls [-lRartdGSs1] [file ...]");
	}
	else if (error == ERRNO || error == MALL_ERR)
		ft_printf("ft_ls: ");
	if (error == ERRNO)
		ft_printf("%s: %s\n", str, strerror(errno));
	if (error == USAGE || error == MALL_ERR)
		exit(EXIT_FAILURE);
	return (0);
}

static int		ft_sort(int argc, char **argv, int (*f)(const char*, const char*))
{
	int		i;
	int		j;
	char	*tab;

	i = -1;
	while (++i < argc)
	{
		j = i - 1;
		tab = argv[i];
		while (j >= 0 && f(argv[j], tab) > 0)
		{
			argv[j + 1] = argv[j];
			j--;
		}
		argv[j + 1] = tab;
	}
	return (0);
}

static t_file	*ft_init(int argc, char **argv, int flag)
{
	int		i;
	t_file	*file;

	file = 0;
	(!argc) ? ft_add_file("", ".", &file) : ft_sort(argc, argv, &ft_strcmp);
	i = -1;
	while (++i < argc)
		if (ft_add_file("", argv[i], &file) == -1 && flag)
			ft_error(argv[i], ERRNO);
	return (file);
}

static int		ft_parse(int argc, char **argv, int *flags)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	*flags = 0;
	while (++i < argc && argv[i][0] == '-' && argv[i][1])
	{
		if (argv[i][1] == '-' && argv[i][2])
			return (i + 1);
		while (*(++argv[i]))
		{
			if ((j = ft_strchr_index("lRartdGSs1", *argv[i])) == -1)
				ft_error(argv[i], USAGE);
			*flags |= (1 << j);
			if ((*argv[i] == '1') || (*argv[i] == 'l'))
				*flags &= (*argv[i] == 'l') ? ~LS_1 : ~LS_L;
		}
	}
	return (i);
}

int				main(int argc, char **argv)
{
	int		i;
	int		flags;
	t_file	*file;
	int		no_files;

	i = ft_parse(argc, argv, &flags);
	argc -= i;
	argv += i;
	file = ft_init(argc, argv, 1);
	no_files = (!file ? 1 : 0);
	ft_print(file, flags, (!no_files ? 1 : 2), argc);
	ft_free_file(&file);
	return (0);
}
