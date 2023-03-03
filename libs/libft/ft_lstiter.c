#include "libft.h"

/* Function name ft_lstiter
Prototype void ft_lstiter(t_list *lst, void (*f)(void *));

f: The address of the function used to iterate on
the list.

Description Iterates the list ’lst’ and applies the function
’f’ on the content of each node.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst && f)
	{
		f(lst->content);
		lst = lst->next;
	}
}
