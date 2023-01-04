/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:55:18 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/13 11:10:12 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, char const *s2)
{
	char			*newstring;
	size_t			len;
	unsigned int	i;
	unsigned int	j;

	len = ft_strlen(s1) + ft_strlen(s2);
	newstring = ft_calloc((len + 1), sizeof(char));
	if (!s1 || !s2 || !newstring)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newstring[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		newstring[i] = s2[j];
		j++;
		i++;
	}
	return (newstring);
}
