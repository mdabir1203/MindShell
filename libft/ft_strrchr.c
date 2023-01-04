/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:07:53 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/05 13:46:38 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	t = (char) c;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == t)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
