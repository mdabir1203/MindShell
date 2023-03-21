#include "../inc/minishell.h"

int	parser_error_check_sub(t_info *info, int i)
{
	if (!strncmp(info->input_lexer[i], "|", 2))
	{
		g_exit_status = 3;
		input_message(PIPE_ERROR_2, 0);
		return (0);
	}
	if (!strncmp(info->input_lexer[i], " ", 1) && \
		!strncmp(info->input_lexer[++i], "|", 2))
	{
		g_exit_status = 2;
		input_message(PIPE_ERROR_1, 0);
		return (0);
	}
	return (1);
}

/**
 * Correct spelling of commands is just for testing. 
 * Needs to be handled proper, later. 
 * //Max added first statement in:
 * if (info->input_lexer[1] != NULL && ..
 * !strncmp(info->input_lexer[0], " ", 1))
 */
int	parser_error_check(t_info *info, t_parse_lexer *pl, int i)
{
	if (!strncmp(info->input_lexer[0], "|", 2))
	{
		g_exit_status = 2;
		input_message(PIPE_ERROR_1, 0);
		return (0);
	}
	if (info->input_lexer[1] != NULL && !strncmp(info->input_lexer[0], " ", 1))
	{
		if (!strncmp(info->input_lexer[++i], "|", 2))
		{
			g_exit_status = 2;
			input_message(PIPE_ERROR_1, 0);
			return (0);
		}
		return (1);
	}
	if (pl->cat == PIPE && info->input_lexer[++i])
	{
		if (!parser_error_check_sub(info, i))
			return (0);
	}
	return (1);
}

/**
 * @brief 
 * @return error() returns 1 if everything goes well BEWARE!!!
 */
int	error(int err, t_info *info)
{
	if (err == ERR_MALLOC_SPLIT || err == ERR_MALLOC_INIT_GROUPS \
		|| err == ERR_MALLOC_SPLIT_ONE || err == ERR_MALLOC_EXPAND_VARIABLES)
		input_message(MALLOC_FAIL, 0);
	if (err == ERR_CMD_NOT_FOUND)
		input_message(STR_WRITE_ERROR, 0);
	if (err == ERR_WRONG_AMOUNT_QUOTATION_MARKS)
		input_message(QUOTATION_MARKS, 0);
	if (err == ERR_NO_EQUAL_IN_EXPORT_ARG)
		input_message(EQUAL_SIGN, 0);
	if (err == ERR_EQUAL_IN_UNSET_ARG)
		input_message(INVALID_IDENTIFIER, 0);
	if (err == ERR_CD_NO_DIRECTORY)
		input_message(REDIRECT_ERROR_1, 0);
	clean_up(err, info);
	return (1);
}
