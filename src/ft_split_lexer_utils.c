#include "../inc/minishell.h"

int	sep(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	red(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	pipesign(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

/**
 * @brief returns ptr to place after the redirect signs
 * saves num of signs in buf if buf is not NULL
 */
char	*after_red(char *str, int *buf)
{
	int	i;

	i = 0;
	while (red(*str) && *str != '\0')
	{
		i++;
		str++;
	}
	if (buf)
		*buf = i;
	return (str);
}
