/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:34:11 by opodolia          #+#    #+#             */
/*   Updated: 2017/03/31 19:19:43 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_col_file(t_file *file, t_index index, t_index max_len, int flags)
{
	int		col;
	int		row;
	t_file	*f;
	int		i;

	i = index.y;
	while (file && i--)
	{
		col = index.x;
		f = file->next;
		while (file && col--)
		{
			ft_print_name(file, flags, max_len.y);
			if (col)
				ft_putnchar(MAX(max_len.x - ft_strlen(file->name), 0), ' ');
			row = index.y;
			while (file && row--)
				file = file->next;
		}
		if (flags & LS_1)
			ft_putchar('\n');
		file = f;
	}
}

static void	ft_print_detail_file(t_file *file, int flags)
{
	int		blocks;
	int		flag;
	int		size[7];

	ft_bzero(size, sizeof(size));
	blocks = 0;
	flag = 1;
	ft_row_size(file, size, &blocks);
	while (file)
	{
		ft_print_items(file, size, flags);
		ft_putchar('\n');
		file = file->next;
	}
}

static void	ft_print_basic_file(t_file *file, int flags)
{
	int		total;
	t_index	max_len;
	t_size	win_size;
	t_index	index;
	t_file	*f;

	total = 0;
	max_len.x = ft_name_maxlen(file) + 1;
	max_len.y = (flags & LS_S) ? ft_blocks_maxlen(file, &total) : 0;
	ioctl(0, TIOCGWINSZ, &win_size);
	index.x = (!(flags & LS_1)) ? win_size.ws_col / (max_len.x + max_len.y) : 1;
	index.y = 0;
	f = file;
	while (f)
	{
		++index.y;
		f = f->next;
	}
	ft_col_file(file, index, max_len, flags);
}

void		ft_print_files(t_file **file, int flags)
{
	ft_sort_all(file, flags);
	if (!(flags & LS_L))
	{
		ft_print_basic_file(*file, flags);
		if (!(flags & LS_1))
			ft_putchar('\n');
	}
	else
		ft_print_detail_file(*file, flags);
}
