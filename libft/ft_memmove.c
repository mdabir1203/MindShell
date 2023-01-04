/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:14:13 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/13 11:05:01 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	unsigned char		*s;

	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	if (!d || !s)
		return (NULL);
	if (d <= s)
		return (ft_memcpy(dst, src, len));
	else
	{
		while (len--)
		{
			d[len] = s[len];
		}
		return (d);
	}
}
