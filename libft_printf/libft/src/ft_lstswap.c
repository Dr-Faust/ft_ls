#include "libft.h"

t_list	*ft_sltswap(t_list *l_1, t_list *l_2)
{
	l_1->next = l_2->next;
	l_2->next = l_1;
	return (l_2);
}
