/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 13:32:27 by opodolia          #+#    #+#             */
/*   Updated: 2017/03/31 19:05:03 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_print_detail(t_file *file, int flags)
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
		if (flag == 1 && !(flags & LS_D))
		{
			ft_printf("total %d\n", blocks);
			flag = 0;
		}
		ft_print_items(file, size, flags);
		ft_putchar('\n');
		file = file->next;
	}
}

void			ft_print_basic(t_file *file, int flags)
{
	int		total;
	t_index	max_len;
	t_size	win_size;
	t_index	index;
	t_file	*f;

	total = 0;
	max_len.x = ft_name_maxlen(file) + 1;
	max_len.y = (flags & LS_S) ? ft_blocks_maxlen(file, &total) : 0;
	if (flags & LS_S)
		ft_printf("total %d\n", total);
	ioctl(0, TIOCGWINSZ, &win_size);
	index.x = (!(flags & LS_1)) ? win_size.ws_col / (max_len.x + max_len.y) : 1;
	index.y = 0;
	f = file;
	while (f)
	{
		++index.y;
		f = f->next;
	}
	if (!(flags & LS_1))
		index.y = (index.y % index.x ? 1 : 0) + (index.y / index.x);
	ft_col(file, index, max_len, flags);
}

static t_file	*ft_read_folder(char path[PATH_MAX], char *name, int flags,
				mode_t mode)
{
	t_file		*file;
	DIR			*folder;
	t_dirent	*entry;

	file = 0;
	if (!(folder = opendir(path)))
	{
		if (!(S_ISREG(mode)))
			ft_error(name, ERRNO);
	}
	else if (!(flags & LS_D))
	{
		while ((entry = readdir(folder)))
			if (entry->d_name[0] != '.' || (flags & LS_A))
				ft_add_file(path, entry->d_name, &file);
	}
	else
		ft_add_file(path, ".", &file);
	if (folder)
		closedir(folder);
	return (file);
}

static void		ft_print_full_path(char *full_path, int argc, int *flag)
{
	if (argc != 0 && argc != 1)
	{
		if (*flag == 2)
		{
			*flag = 1;
			ft_printf("%s:\n", full_path);
		}
		else
			ft_printf("\n%s:\n", full_path);
	}
}

void			ft_print(t_file *file, int flags, int flag, int argc)
{
	t_file	*f;

	f = file;
	if (!(flags & LS_RR) && !flag)
		return ;
	while (f)
	{
		if ((S_ISDIR(f->mode)) && (flag ||
			(ft_strcmp(f->name, ".") &&
			ft_strcmp(f->name, ".."))))
		{
			ft_print_full_path(f->full_path, argc, &flag);
			file = ft_read_folder(f->full_path, f->name, flags, f->mode);
			if (file)
			{
				ft_file(&file, flags);
				ft_print(file, flags, 0, -1);
				ft_free_file(&file);
			}
		}
		f = f->next;
	}
}
