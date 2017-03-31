/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 18:40:29 by opodolia          #+#    #+#             */
/*   Updated: 2017/03/31 11:27:50 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_time(t_file *file)
{
	time_t	now;
	char	*str;

	time(&now);
	str = ctime(&(file->time)) + 4;
	if (now - file->time > HALF_YEAR_SEK)
	{
		str[7] = ' ';
		ft_strncpy(&(str[8]), &(str[16]), 5);
	}
	ft_printf(" %.12s ", str);
}

static char	ft_file_acl(char path[PATH_MAX])
{
	acl_t	tmp;
	char	str[101];

	if (listxattr(path, str, sizeof(str), XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((tmp = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		acl_free(tmp);
		return ('+');
	}
	return (' ');
}

static char	ft_file_type(int mode)
{
	mode = (mode & S_IFMT);
	if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISREG(mode))
		return ('-');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('-');
}

static void	ft_print_chmod(char str[12], int mode, char path[PATH_MAX])
{
	str[0] = ft_file_type(mode);
	str[1] = (S_IRUSR & mode) ? 'r' : '-';
	str[2] = (S_IWUSR & mode) ? 'w' : '-';
	str[3] = (S_IXUSR & mode) ? 'x' : '-';
	str[4] = (S_IRGRP & mode) ? 'r' : '-';
	str[5] = (S_IWGRP & mode) ? 'w' : '-';
	str[6] = (S_IXGRP & mode) ? 'x' : '-';
	str[7] = (S_IROTH & mode) ? 'r' : '-';
	str[8] = (S_IWOTH & mode) ? 'w' : '-';
	str[9] = (S_IXOTH & mode) ? 'x' : '-';
	str[10] = ft_file_acl(path);
	str[11] = '\0';
	if (S_ISUID & mode)
		str[3] = (str[3] == '-') ? 'S' : 's';
	if (S_ISGID & mode)
		str[6] = (str[6] == '-') ? 'S' : 's';
	if (S_ISVTX & mode)
		str[9] = (str[9] == '-') ? 'T' : 't';
	ft_putstr(str);
}

void		ft_print_items(t_file *file, int size[7], int flags)
{
	char	buff[NAME_MAX + 1];
	char	str[12];

	(flags & LS_S) ? ft_printf("%*hu ", size[0], file->blocks) : 0;
	ft_print_chmod(str, file->mode, file->full_path);
	ft_printf(" %*hu", size[1], file->nlink);
	ft_printf(" %-*s", size[2], getpwuid(file->uid)->pw_name);
	ft_printf("  %-*s", size[3], getgrgid(file->gid)->gr_name);
	if (str[0] != 'c' && str[0] != 'b')
		ft_printf("  %*lld", size[4], file->size);
	else
	{
		ft_printf(" %*d", size[5], major(file->rdev));
		ft_printf(", %*d", size[6], minor(file->rdev));
	}
	ft_print_time(file);
	if (str[0] != 'l')
		ft_print_name(file, flags, 0);
	else
	{
		ft_bzero(buff, NAME_MAX + 1);
		readlink(file->full_path, buff, NAME_MAX);
		ft_print_link(file, flags, buff);
	}
}
