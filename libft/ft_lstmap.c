/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:51:59 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/14 15:36:19 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*newlst;
	t_list	*newnode;

	if (!lst || !f)
		return (NULL);
	newlst = 0;
	newnode = 0;
	while (lst)
	{
		newnode = ft_lstnew((f)(lst->content));
		if (newnode == NULL)
		{
			ft_lstclear(&lst, del);
			free(newnode);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newnode);
		lst = lst->next;
	}
	return (newlst);
}
