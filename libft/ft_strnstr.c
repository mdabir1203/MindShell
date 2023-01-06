/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:14:23 by nrenz             #+#    #+#             */
/*   Updated: 2023/01/06 15:08:18 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;
	//size_t	h_len;

	n_len = ft_strlen(needle);
	//h_len = ft_strlen(haystack);
	ft_strlen(haystack);
	if (!haystack || !needle)
		return (NULL);
	if (!needle || !needle[0])
		return ((char *)haystack);
	while (len >= n_len && *haystack != '\0')
	{
		if (ft_memcmp(haystack, needle, n_len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
