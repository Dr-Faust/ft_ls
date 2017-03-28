#include "ft_ls.h"

static int	ft_sort_ascii(t_file *file)
{
	if (!file)
		return (0);
	if (file->next && ft_strcmp(file->name, file->next->name) > 0)
		(t_file *)file = ft_lstswap((t_file *)file, (t_file *)file->next);
	file->next = ft_sort_ascii(file->next);
	if (file->next && ft_strcmp(file->name, file->next->name) > 0)
	{
		(t_file *)file = ft_lstswap((t_file *)file, (t_file *)file->next);
		file->next = ft_sort_ascii(file->next);
	}
	return (file);
}

int			ft_sort(t_file **file, int flags)
{
	*file = ft_sort_ascii(*file);
	if (flags & LS_T)
		*file = ft_sort_time(*file);
}
