#include "../inc/minishell.h"

int	only_separator_in_string(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!sep(str[i]))
			return (0);
	}
	return (1);
}

int	categorize_pipe(char *str)
{
	if (!ft_strncmp(str, "<<", 3))
		return (REDIR_INPUT_APPEND);
	if (!ft_strncmp(str, "<", 2))
		return (REDIR_INPUT);
	if (!ft_strncmp(str, ">", 2))
		return (REDIR_OUTPUT);
	if (!ft_strncmp(str, ">>", 3))
		return (REDIR_OUTPUT_APPEND);
	if (!ft_strncmp(str, "|", 2))
		return (PIPE);
	return (WORD);
}

int	categorize_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", 5))
		return (CMD_ECHO);
	if (!ft_strncmp(str, "exit", 5))
		return (CMD_EXIT);
	if (!ft_strncmp(str, "cd", 3))
		return (CMD_CD);
	if (!ft_strncmp(str, "pwd", 4))
		return (CMD_PWD);
	if (!ft_strncmp(str, "export", 7))
		return (CMD_EXPORT);
	if (!ft_strncmp(str, "unset", 6))
		return (CMD_UNSET);
	if (!ft_strncmp(str, "env", 4))
		return (CMD_ENV);
	if (!ft_strncmp(str, "clear", 5))
		return (CMD_CLEAR);
	return (WORD);
}

int	categorize_flag(char *str)
{
	if (!ft_strncmp(str, "-", 1))
		return (FLAG);
	if (only_separator_in_string(str))
		return (SEPARATOR);
	return (WORD);
}

int	categorize(char *str)
{
	int	category;

	category = categorize_pipe(str);
	if (category != WORD)
		return (category);
	category = categorize_builtin(str);
	if (category != WORD)
		return (category);
	category = categorize_flag(str);
	if (category != WORD)
		return (category);
	return (WORD);
}
