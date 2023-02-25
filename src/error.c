
#include "../inc/minishell.h"

/**
 * Correct spelling of commands is just for testing. Needs to be handled proper, later. 
 */
int	parser_error_check(t_info *info, t_parse_lexer *pl, int i)
{
	if (!strncmp(info->input_lexer[0], "|", 2))
	{
		input_message(PIPE_ERROR_1, 0);
		return (0);
	}
	if (!strncmp(info->input_lexer[0], " ", 1))
	{
		if (!strncmp(info->input_lexer[++i], "|", 2))
			{
				input_message(PIPE_ERROR_1, 0);
				return (0);
			}
		return (1);
	}
	if (pl->cat == PIPE)
	{
		if(!strncmp(info->input_lexer[++i], "|", 2))
		{
			input_message(PIPE_ERROR_2, 0);
			return (0);
		}
		printf("i2 %d\n", i);
		if (!strncmp(info->input_lexer[i], " ", 1) && !strncmp(info->input_lexer[++i], "|", 2))
		{
			input_message(PIPE_ERROR_1, 0);
			return (0);
		}		
	}
	return (1);
}

int	executer_error_check(t_info *info, t_group *groups)
{
	(void) info;
	if (groups[0].redir_in == REDIR_INPUT)
	{
			//input_message(REDIRECT_ERROR_1, 0);
			//return (0);
	}
	return (1);
}

/**
 * @brief 
 * @return error() returns 1 if everything goes well BEWARE!!!
 */
int	error(int err, t_info *info)
{
	printf("ERROR\n");
	input_message(ERROR, 0);
	if (err == ERR_MALLOC_SPLIT || err == ERR_MALLOC_INIT_GROUPS \
		|| err == ERR_CMD_NOT_FOUND || err == ERR_MALLOC_SPLIT_ONE) //need to free something here?
	{
		input_message(MALLOC_FAIL, 0);			//let's do this or
		//printf("While memory allocation\n");	// this ?
	}
	if (err == ERR_CMD_NOT_FOUND)
	{
		input_message(STR_WRITE_ERROR, 0);
		//printf("Minishell: command not found\n");
	}
	if (err == ERR_WRONG_AMOUNT_QUOTATION_MARKS)
	{
		input_message(QUOTATION_MARKS, 0);
		//printf("Wrong amount of quotation marks\n");
	}
	if (err == ERR_NO_EQUAL_IN_EXPORT_ARG)
	{
		input_message(EQUAL_SIGN, 0);
		//printf("No '=' sign in export argument\n");
	}
	if (err == ERR_EQUAL_IN_UNSET_ARG)
	{
		input_message(INVALID_IDENTIFIER, 0);
		//printf("Not a valid identifier\n");
	}
	clean_up(err, info);
	return (1);
	//return(0);
}
