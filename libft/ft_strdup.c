/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:24:30 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/13 11:09:23 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	strsize;

	if (!s1)
		return (NULL);
	strsize = ft_strlen(s1);
	s2 = malloc((strsize + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, strsize + 1);
	return (s2);
}
