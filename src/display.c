/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:46:00 by opodolia          #+#    #+#             */
/*   Updated: 2017/03/28 19:36:00 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ft_display_basic(t_file *file, int flags)
{

}

static t_file	*ft_read_folder(char path[PATH_MAX], char *name, int flags)
{
	t_file		*file;
	DIR			*folder;
	t_dirent	*entry;

	file = 0;
	if (!(folder = opendir(path)))
		ft_error(name, ERRNO);
	else if (!(flags & LS_D))
	{
		while ((entry = readdir(folder)))
			if (entry->d_name[0] != '.' || (flags & LS_A))
				ft_add_file(parh, entry->d_name, &file);
	}
	else
		ft_add_file(path, ".", &file);
	if (folder)
		closedir(folder);
	return (file);
}

static void		ft_display_full_path(char *full_path, int argc, int *flag)
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

void			ft_display(t_file *file, int flags, int flag, int argc)
{
	t_file	*f;

	f = file;
	if ((flags & LS_RR) && flag)
	{
		while (f)
		{
			if (S_ISDIR(f->mode) && (flag || (ft_strcmp(f->name, ".") &&
				ft_strcmp(f->name, ".."))))
			{
				ft_display_full_path(f->full_path, argc, &flag);
				file = ft_read_folder(f->full_path, f->name, flags);
				if (file)
				{
					ft_sort(&file, flags);
					if (!flags & LS_L)
						ft_display_basic(file, flags);

					ft_display(file, flags, 0, -1);
				}
			}
		}
	}
}
