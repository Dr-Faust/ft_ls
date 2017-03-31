/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:48:48 by opodolia          #+#    #+#             */
/*   Updated: 2017/03/30 13:34:52 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free_file(t_file **file)
{
	while (*file)
	{
		free((*file)->name);
		free(*file);
		*file = (*file)->next;
	}
}

t_file	*ft_file_swap(t_file *f_1, t_file *f_2)
{
	f_1->next = f_2->next;
	f_2->next = f_1;
	return (f_2);
}

int		ft_int_len(int numb)
{
	int		len;

	len = 1;
	while (numb / 10)
	{
		numb /= 10;
		len++;
	}
	return (len);
}

int		ft_blocks_maxlen(t_file *file, int *total)
{
	int		max_len;

	max_len = 0;
	while (file)
	{
		max_len = MAX(ft_int_len(file->blocks), max_len);
		*total += file->blocks;
		file = file->next;
	}
	return (max_len);
}

int		ft_name_maxlen(t_file *file)
{
	int		max_len;

	max_len = 0;
	while (file)
	{
		max_len = MAX((int)ft_strlen(file->name), max_len);
		file = file->next;
	}
	return (max_len);
}
