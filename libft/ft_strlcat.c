/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:58:36 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/13 11:11:09 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	counter;

	srcsize = 0;
	counter = 0;
	while (dst[counter] && counter < dstsize)
		counter++;
	while ((counter + srcsize + 1) < dstsize && (src[srcsize]))
	{
		dst[counter + srcsize] = src[srcsize];
		srcsize++;
	}
	if (counter != dstsize)
		dst[counter + srcsize] = '\0';
	return (counter + ft_strlen(src));
}
