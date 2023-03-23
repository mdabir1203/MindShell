#include "../inc/minishell.h"

int	is_redirect(int num)
{
	if (num == REDIR_INPUT_APPEND)
		return (1);
	if (num == REDIR_INPUT)
		return (1);
	if (num == REDIR_OUTPUT_APPEND)
		return (1);
	if (num == REDIR_OUTPUT)
		return (1);
	return (0);
}

// *ret = 1; in the if before the two ifs
int	found_save_redirect_sub(int *before_cat, t_info *info, \
	char *act_lexer, t_parse_lexer *pl)
{
	if (is_redirect(*before_cat))
	{
		if (pl->cat == WORD || pl->cat == FLAG || \
			(pl->cat > BUILTIN_START && pl->cat < BUILTIN_END))
		{
			if (*before_cat == REDIR_INPUT_APPEND || \
				*before_cat == REDIR_INPUT)
				info->groups[pl->act_group].redir_infile = act_lexer;
			if (*before_cat == REDIR_OUTPUT_APPEND || \
				*before_cat == REDIR_OUTPUT)
				info->groups[pl->act_group].redir_outfile = act_lexer;
			*before_cat = 0;
			return (1);
		}
	}
	return (0);
}

/**
 * @brief only call ONCE in the loop? it changes status it is called
 * it returns 1 if it identifies the given str as an redirect 
 * i.e. (">", " ", "filename")
 * else returns 0
 * it saves the redirect in the struct groups
 */
int	found_save_redirect(t_parse_lexer *pl, t_info *info, \
	char *act_input_lexer_str, int i)
{
	int			ret;
	static int	before_cat = 0;

	ret = 0;
	if (pl->act_group == 0 && i == 0)
		before_cat = 0;
	if (pl->cat == REDIR_INPUT_APPEND || pl->cat == REDIR_INPUT)
	{
		ret = 1;
		before_cat = pl->cat;
		info->groups[pl->act_group].redir_in = pl->cat;
	}
	if (pl->cat == REDIR_OUTPUT_APPEND || pl->cat == REDIR_OUTPUT)
	{
		ret = 1;
		before_cat = pl->cat;
		info->groups[pl->act_group].redir_out = pl->cat;
	}
	if (pl->cat == SEPARATOR && is_redirect(before_cat))
		ret = 1;
	if (found_save_redirect_sub(&before_cat, info, \
		act_input_lexer_str, pl) == 1)
		ret = 1;
	return (ret);
}

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo\0", 5))
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
	return (0);
}
