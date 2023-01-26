#include "../inc/minishell.h"

int categorize(char *str)
{
	if (!ft_strncmp(str, "<<", 3)) // does it really compare with \0 the last sign, please check
		return (REDIR_INPUT_APPEND);
	if (!ft_strncmp(str, "<", 2))
		return (REDIR_INPUT);
	if (!ft_strncmp(str, ">", 2))
		return (REDIR_OUTPUT);
	if (!ft_strncmp(str, ">>", 3))
		return (REDIR_OUTPUT_APPEND);
	if (!ft_strncmp(str, "|", 2))
		return (PIPE);
	if (!ft_strncmp(str, SEPARATOR_ONE, 1)) // doppelt - da im lexer auch schon unterschieden
		return (SEPARATOR);
	if (!ft_strncmp(str, SEPARATOR_TWO, 1)) // not really good, only compares the first character
		return (SEPARATOR);
	if (!ft_strncmp(str, SEPARATOR_THREE, 1))
		return (SEPARATOR);
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
	if (!ft_strncmp(str, "-", 1))
		return (FLAG);
	return (WORD);
}
