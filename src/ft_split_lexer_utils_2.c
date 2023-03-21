#include "../inc/minishell.h"

char	*after_sep(char *str, int *buf)
{
	int	i;

	i = 0;
	while (sep(*str) && *str != '\0')
	{
		i++;
		str++;
	}
	if (buf)
		*buf = i;
	return (str);
}

char	*after_pipe(char *str, int *buf)
{
	if (buf)
		*buf = 1;
	return (++str);
}

char	*after_quote(char *str, int *buf)
{
	int		i;
	int		i_word;
	char	start_quote;

	i_word = 0;
	start_quote = *str;
	i = 1;
	str++;
	while (*str != start_quote)
	{
		i++;
		str++;
	}
	i++;
	str++;
	if (!sep(*str) && !red(*str) && *str != '\0')
		str = after_word(str, &i_word);
	if (buf)
		*buf = i + i_word;
	return (str);
}

char	*after_word(char *str, int *buf)
{
	int	i;
	int	i_quote;

	i = 0;
	i_quote = 0;
	while (!sep(*str) && !red(*str) && !pipesign(*str) && *str != '\0')
	{
		if (quote(*str))
			str = after_quote(str, &i_quote);
		else
		{
			i++;
			str++;
		}
	}
	if (buf)
		*buf = i + i_quote;
	return (str);
}

/**
 * @brief shall count how many character, separator, 
 * redirect, etc. parts we have
 */
int	count_parts(char *str)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		if (sep(*str))
			str = after_sep(str, NULL);
		else if (red(*str))
			str = after_red(str, NULL);
		else if (quote(*str))
			str = after_quote(str, NULL);
		else if (pipesign(*str))
			str = after_pipe(str, NULL);
		else
			str = after_word(str, NULL);
		i++;
	}
	return (i);
}
