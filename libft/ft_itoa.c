/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:59:18 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/13 11:04:03 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static long long	ft_inttolong(int n)
{
	long long	long_n;

	long_n = (long long)n;
	if (long_n < 0)
	{
		long_n = long_n * -1;
	}
	return (long_n);
}

char	*ft_itoa(int n)
{
	char		*p;
	int			i;
	int			j;
	char		c[11];
	long long	ln;

	ln = ft_inttolong(n);
	i = 0;
	while (ln > 0)
	{
		c[i++] = (ln % 10) + '0';
		ln = ln / 10;
	}
	if (n == 0)
		c[i++] = '0';
	if (n < 0)
		c[i++] = '-';
	p = ft_calloc((i + 1), sizeof(char));
	if (!p)
		return (NULL);
	j = 0;
	i = i - 1;
	while (i >= 0)
		p[j++] = c[i--];
	return (p);
}
