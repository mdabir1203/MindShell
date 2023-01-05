/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:57:30 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/17 14:23:49 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static unsigned int	ft_wordcount(const char *s, char delim)
{
	unsigned int	i;
	unsigned int	wordcounter;
	unsigned int	marker;

	i = 0;
	wordcounter = 0;
	marker = 0;
	while (s[i] != '\0')
	{
		if (s[i] != delim && marker == 0)
		{
			wordcounter++;
			marker = 1;
		}
		if (s[i] == delim)
			marker = 0;
		i++;
	}
	return (wordcounter);
}

static unsigned int	ft_wordlength(const char *s, char delim)
{
	unsigned int	wordlen;

	wordlen = 0;
	while (s[wordlen] != delim && s[wordlen] != '\0')
		wordlen++;
	return (wordlen);
}

static void	ft_fill_array(char const *s, char c, unsigned int wordcount,
	char **newstrings)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	wordlen;

	i = 0;
	j = 0;
	while (i < wordcount)
	{
		if (s[j] != c)
		{
			wordlen = ft_wordlength(s + j, c);
			newstrings[i] = ft_calloc(wordlen + 1, sizeof(char));
			ft_strlcpy(newstrings[i++], s + j, wordlen + 1);
			j += wordlen;
		}
		else
			j++;
	}
	newstrings[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char			**newstrings;
	unsigned int	wordcount;

	wordcount = ft_wordcount(s, c);
	newstrings = ft_calloc(wordcount + 1, sizeof(char *));
	if (!s || !newstrings)
		return (NULL);
	ft_fill_array(s, c, wordcount, newstrings);
	return (newstrings);
}
