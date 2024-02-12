#include "list.h"


t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	int	    swap;
	t_list	*tmp;

	tmp = lst;
	while(lst->next)
	{
		if (((*cmp)(lst->content, lst->next->content)) == 0)
		{
			swap = lst->content;
			lst->content = lst->next->content;
			lst->next->content = swap;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}