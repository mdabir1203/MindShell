
#include "../inc/minishell.h"

void	input_error_check(char **cmd)
{
	if (!strncmp(cmd[0], "Echo", 5) || !strncmp(cmd[0], "Exit", 5))
	{
        input_message(STR_LETTER_ERROR, 0);
        //printf("Write 'echo'!\n");
        return ;
	}
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
		|| err == ERR_CMD_NOT_FOUND) //need to free something here?
	{
		input_message(MALLOC_FAIL, 0);			//let's do this or
		//printf("While memory allocation\n");	// this ?
	}
	if (err == ERR_CMD_NOT_FOUND)
	{
		printf("Minishell: command not found\n");
	}
	clean_up(err, info);
	return (1);
	//return(0);
}
