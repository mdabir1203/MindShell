
#include "../inc/minishell.h"

int	input_error_check(t_info *info, t_group *groups)
{
	if (!strncmp(info->input_lexer[0], "|", 2))
	{
		input_message(PIPE_ERROR_1, 0);
		return (0);
	}
	if (!strncmp(info->input_lexer[0], "Exit", 5))	// several error messages appeal; tidy up!!!
	{
		input_message(EXIT_ERROR_1, 0);
		return (0);
	}
	if (groups[0].redir_in == REDIR_INPUT)
	{
			input_message(REDIRECT_ERROR_1, 0);
			return (0);
	}
	/*if (!strncmp(cmd[0], "Echo", 5))
	{
        input_message(STR_LETTER_ERROR, 0);
        //printf("Write 'echo'!\n");
        return ;
	}*/
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
		printf("Minishell: command not found\n");
	}
	if (err == ERR_WRONG_AMOUNT_QUOTATION_MARKS)
	{
		printf("Wrong amount of quotation marks\n");
	}
	clean_up(err, info);
	return (1);
	//return(0);
}
