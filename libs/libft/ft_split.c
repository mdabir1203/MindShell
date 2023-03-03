#include "libft.h"

// end of word is either the separator or the end of str
static	int	wordsize(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !(str[i] == c))
	{
		++i;
	}
	return (i);
}

static	int	count_words(char const *s, char c)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (s[0] == 0)
		return (0);
	if (s[0] != c)
		count++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			++count;
		++i;
	}
	return (count);
}

static	char	*next_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c)
		i++;
	return ((char *)s + i);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	char	*act_word;
	int		word_count;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	ptr = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	act_word = next_word((char *)s, c);
	while (i < word_count)
	{
		ptr[i] = malloc(wordsize(act_word, c) + 1);
		if (ptr == NULL)
			return (NULL);
		ft_strlcpy(ptr[i], act_word, (wordsize(act_word, c) + 1));
		act_word = act_word + wordsize(act_word, c);
		act_word = next_word(act_word, c);
		++i;
	}
	ptr[word_count] = NULL;
	return (ptr);
}
