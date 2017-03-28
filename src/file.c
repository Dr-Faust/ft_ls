#include "ft_ls.h"

static int	ft_full_path(char path[PATH_MAX], char *name,
			char full_path[PATH_MAX])
{
	int		i;

	i = -1;
	while (path[++i])
		full_path[i] = path[i];
	if (i && i < PATH_MAX)
		if (!(path[0] == '/' && path[1] == '\0'))
			full_path[i++] = '/';
	while (*name && i < PATH_MAX)
		full_path[i++] = *name++;
	if (i < PATH_MAX)
		full_path[i++] = *name++;
	if (i < PATH_MAX)
		full_path[i] = '\0';
	else
		errno = ENAMETOOLONG;
	return ((i < PATH_MAX) ? 1 : 0);
}

static t_file	ft_init_file(char path[PATH_MAX], char *name, t_stat *stat)
{
	t_file	*init;

	if (!(new = ft_memalloc(sizeof(t_file))) ||
		(!(new->name = ft_strdup(name))))
		ft_error(NULL, MALL_ERR);
	init->mode = stat->st_mode;
	init->nlink = stat->st_nlink;
	init->uid = stat->st_uid;
	init->gid = stat->st_gid;
	init->rdev = stat->st_rdev;
	init->size = stat->st_size;
	init->time = stat->st_mtime;
	init->ntime = stat->st_mtimensec;
	init->blocks = stat->st_blocks;
	ft_full_path(path, name, init->full_path);
	new->next = 0;
	return (init);
}

int			ft_add_file(char path[PATH_MAX], char *name, t_file **file)
{
	char	full_path[PATH_MAX];
	t_stat	stat;

	if (!(ft_full_path(path, name, full_path)))
	{
		ft_error(name, USAGE);
		return (-1);
	}
	if (lstat(full_path, &stat) == -1)
		return (-1);
	if (!(*file))
		*file = ft_init_file(path, name, &stat);
	else
	{
		while ((*file)->next)
			lst = &((*file)->next);
		(*file)->next = ft_init_file(path, name, &stat);
	}
	return (0);
}
