/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:53:28 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/13 11:14:23 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char				*substring;
	unsigned int		i;

	substring = malloc((len + 1) * sizeof(char));
	if (!s || !substring)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
	{
		substring[0] = '\0';
		return (substring);
	}
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
