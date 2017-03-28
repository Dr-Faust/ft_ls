#include "ft_ls.h"

static int		ft_display_file(t_file **file, int flags)
{
	ft_sort(file, flags);
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

int				ft_display(t_file *file, int flags, int	flag, int argc)
{
	t_file	*f;

	f = file;
	if (!(flags & LS_RR) && !flag)
		return (1);
	while (f)
	{
		if (S_ISDIR(f->mode) && (flag || (ft_strcmp(f->name, ".") &&
			ft_strcmp(f->name, ".."))))
		{
			ft_display_full_path(f->full_path, argc, &flag);
			file = ft_read_folder(f->full_path, f->name, flags);
			if (file)
			{
				ft_display_file(&file, flags);
			}
		}
	}
}
