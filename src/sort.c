/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:46:12 by opodolia          #+#    #+#             */
/*   Updated: 2017/03/29 21:32:10 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*ft_reverse(t_file *file)
{
	t_file	*prev;
	t_file	*curr;
	t_file	*next;

	prev = 0;
	curr = file;
	next = file->next;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return (prev);
}

static t_file	*ft_sort_size(t_file *file)
{
	if (!file)
		return (0);
	if (file->next && file->size < file->next->size)
		file = ft_file_swap(file, file->next);
	file->next = ft_sort_size(file->next);
	if (file->next && file->size < file->next->size)
	{
		file = ft_file_swap(file, file->next);
		file->next = ft_sort_size(file->next);
	}
	return (file);
}

static t_file	*ft_sort_time(t_file *file)
{
	if (!file)
		return (0);
	if (file->next && (file->time < file->next->time))
		file = ft_file_swap(file, file->next);
	else if (file->next && file->time == file->next->time)
		if (file->next && (file->ntime < file->next->ntime))
			file = ft_file_swap(file, file->next);
	file->next = ft_sort_time(file->next);
	if (file->next && file->time < file->next->time)
	{
		file = ft_file_swap(file, file->next);
		file->next = ft_sort_time(file->next);
	}
	else if (file->next && file->time == file->next->time)
		if (file->next && file->ntime < file->next->ntime)
		{
			file = ft_file_swap(file, file->next);
			file->next = ft_sort_time(file->next);
		}
	return (file);
}

static t_file	*ft_sort_ascii(t_file *file)
{
	if (!file)
		return (0);
	if (file->next && ft_strcmp(file->name, file->next->name) > 0)
		file = ft_file_swap(file, file->next);
	file->next = ft_sort_ascii(file->next);
	if (file->next && ft_strcmp(file->name, file->next->name) > 0)
	{
		file = ft_file_swap(file, file->next);
		file->next = ft_sort_ascii(file->next);
	}
	return (file);
}

int				ft_sort_all(t_file **file, int flags)
{
	*file = ft_sort_ascii(*file);
	if (flags & LS_T)
		*file = ft_sort_time(*file);
	if (flags & LS_SS)
		*file = ft_sort_size(*file);
	if (flags & LS_R)
		*file = ft_reverse(*file);
	return (0);
}
