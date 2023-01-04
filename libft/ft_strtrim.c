/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:56:37 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/13 11:13:50 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	unsigned int	i;
	unsigned int	j;
	size_t			len;
	char			*newstring;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) != 0 && i < ft_strlen(s1))
		i++;
	while (ft_strrchr(set, s1[j]) != 0 && j > 1)
		j--;
	if (i > j)
		return (ft_strdup(""));
	len = j - i + 1;
	newstring = malloc((len + 1) * sizeof(char));
	if (!newstring)
		return (NULL);
	ft_strlcpy(newstring, &s1[i], len + 1);
	return (newstring);
}
