/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_col.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 18:08:25 by opodolia          #+#    #+#             */
/*   Updated: 2017/03/29 21:22:43 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_name(t_file *file, int flags, int len)
{
	if (len)
	{
		ft_putnchar(MAX(len - ft_int_len(file->blocks), 0), ' ');
		ft_printf("%d ", file->blocks);
	}
	if (flags & LS_G)
	{
		if (S_ISDIR(file->mode))
			ft_printf("%s%s%s", CYAN, file->name, NORMAL);
		else if (S_ISBLK(file->mode))
			ft_printf("%s%s%s", BL_CYAN, file->name, NORMAL);
		else if (S_ISCHR(file->mode))
			ft_printf("%s%s%s", BL_YELLOW, file->name, NORMAL);
		else if (S_ISLNK(file->mode))
			ft_printf("%s%s%s", MAGENTA, file->name, NORMAL);
		else
			(S_IXUSR & file->mode) ?
				ft_printf("%s%s%s", RED, file->name, NORMAL) :
				ft_printf("%s", file->name);
	}
	else
		ft_printf("%s", file->name);
}

void		ft_col(t_file *file, t_index index, t_index max_len, int flags)
{
	int		col;
	int		row;
	t_file	*f;
	int		i;

	i = -1;
	while (file && i++ < index.y)
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
		ft_putchar('\n');
		file = f;
	}
}

void		ft_row_size(t_file *file, int size[7], int *blocks)
{
	int		len;

	size[5] = 3;
	size[6] = 3;
	while (file)
	{
		size[0] = MAX(ft_int_len(file->blocks), size[0]);
		size[1] = MAX(ft_int_len(file->nlink), size[1]);
		size[2] = MAX((int)ft_strlen(getpwuid(file->uid)->pw_name), size[2]);
		size[3] = MAX((int)ft_strlen(getgrgid(file->gid)->gr_name), size[3]);
		if (!S_ISCHR(file->mode))
			len = ft_int_len(file->size);
		else
		{
			size[5] = MAX(ft_int_len(major(file->rdev)), size[5]);
			size[6] = MAX(ft_int_len(minor(file->rdev)), size[6]);
			len = size[5] + size[6] + 2;
		}
		size[4] = MAX(len, size[4]);
		*blocks += file->blocks;
		file = file->next;
	}
	size[5] = MAX(size[4] - size[6] - 1, size[5]);
}
