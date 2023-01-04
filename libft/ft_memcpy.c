/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:12:40 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/11 12:05:57 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	counter;

	d = (char *) dst;
	s = (char *) src;
	if (d == NULL && s == NULL)
		return (NULL);
	counter = 0;
	while (counter < n)
	{
		*d = *s;
		counter++;
		s++;
		d++;
	}
	return (dst);
}
