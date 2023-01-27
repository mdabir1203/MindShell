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

int	found_save_executable(t_parse_lexer *pl, t_info *info, char *act_input_lexer_str, int i) // malloc so groß wie der lexer string ist
{
	static int already_found_exe = 0;

	if (pl->cat == PIPE || i == 0)
		already_found_exe = 0;
	if (already_found_exe == 0 && !pl->is_red && pl->cat != PIPE && pl->cat != SEPARATOR)// (pl->cat == WORD || pl->cat == FLAG || (pl->cat > BUILTIN_START && pl->cat < BUILTIN_END)))
	{
		info->groups[pl->act_group].cmd = act_input_lexer_str;
		pl->is_exe = 1;
		already_found_exe = 1;
		return (pl->is_exe);
	}
	if (act_input_lexer_str == NULL)
		already_found_exe = 0;
	pl->is_exe = 0;
	return (pl->is_exe);
}

/**
 * @brief only call ONCE in the loop? it changes status it is called
 * it returns 1 if it identifies the given str as an redirect i.e. (">", " ", "filename")
 * else returns 0
 * it saves the redirect in the struct groups
 */
int	found_save_redirect(t_parse_lexer *pl, t_info *info, char *act_input_lexer_str) // in init set everything to NULL or 0
{
	int ret;
	static int before_cat = 0;

	ret = 0;
	if (pl->cat == REDIR_INPUT_APPEND || pl->cat == REDIR_INPUT)
	{
		ret = 1;
		before_cat = pl->cat;
		info->groups[pl->act_group].redirect_input = pl->cat;
	}
	if (pl->cat == REDIR_OUTPUT_APPEND || pl->cat == REDIR_OUTPUT)
	{
		ret = 1;
		before_cat = pl->cat;
		info->groups[pl->act_group].redirect_output = pl->cat;
	}
	if (pl->cat == SEPARATOR && is_redirect(before_cat))
		ret = 1;
	if (is_redirect(before_cat))
	{
		if (pl->cat == WORD || pl->cat == FLAG || (pl->cat > BUILTIN_START && pl->cat < BUILTIN_END))
		{
			ret = 1;
			if (before_cat == REDIR_INPUT_APPEND || before_cat == REDIR_INPUT)
				info->groups[pl->act_group].redirect_input_filename = act_input_lexer_str;
			if (before_cat == REDIR_OUTPUT_APPEND || before_cat == REDIR_OUTPUT)
				info->groups[pl->act_group].redirect_output_filename = act_input_lexer_str;
			before_cat = 0;
		}
	}
	return (ret);
}

int	count_groups(t_info *info)
{
	int num_groups;
	int run;

	num_groups = 1;
	run = -1;
	while (info->input_lexer[++run])
	{
		if (!ft_strncmp(info->input_lexer[run], "|", 2))
			num_groups++;
	}
	return (num_groups);
}