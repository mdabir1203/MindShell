/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:23:57 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/05 17:08:52 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pnt;

	pnt = malloc(size * count);
	if (!pnt)
		return (NULL);
	if (pnt)
		ft_bzero(pnt, size * count);
	return (pnt);
}
