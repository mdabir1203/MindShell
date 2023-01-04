/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:00:13 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/13 11:12:06 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	res = ft_strdup(s);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = (f)(i, s[i]);
		i++;
	}
	return (res);
}

char	ft_testfunction(unsigned int i, char c)
{
	i = 0;
	if (c >= 'a' && c <= 'z')
		c -= 'A' - 'a';
	if (c >= 'A' && c <= 'Z')
		c += 'A' - 'a';
	return (c);
}
