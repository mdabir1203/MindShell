#include "libft.h"

/* Function name ft_lstmap
Prototype t_list *ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *));
Turn in files -  Parameters lst: The address of a plst to a node.
f: The address of the function used to iterate on
the list. del: The address of the function used to delete
the content of a node if needed.
Return value The new list.NULL if the allocation fails.
External functs. malloc, free
Description Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new   
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*firstelement;

	if (!lst)
		return (NULL);
	firstelement = ft_lstnew(f(lst->content));
	if (!firstelement)
		return (NULL);
	new = firstelement;
	while (lst->next)
	{
		lst = lst->next;
		new->next = ft_lstnew(f(lst->content));
		if (!new->next)
		{
			ft_lstclear(&firstelement, del);
			return (NULL);
		}
		new = new->next;
	}
	return (firstelement);
}
