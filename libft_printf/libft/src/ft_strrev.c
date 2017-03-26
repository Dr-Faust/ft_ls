/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 06:25:21 by opodolia          #+#    #+#             */
/*   Updated: 2017/03/09 06:30:53 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *s)
{
	char	*str;
	char	c;

	if (!s)
		return ;
	str = s;
	while (*str)
		str++;
	str--;
	while (s < str)
	{
		c = *s;
		*s++ = *str;
		*str-- = c;
	}
}
