/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:02:41 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/05 13:53:52 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	int			i;
	char		l;

	l = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == l)
			return ((char *)s + i);
		i++;
	}
	if ((l == 0) && (s[i] == l))
		return ((char *)s + i);
	else
		return (NULL);
}
