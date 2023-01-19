
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

int	error(int err)
{
	//printf("ERROR\n");
	input_message(ERROR, 0);
	if (err == ERR_MALLOC_SPLIT)
	{
		input_message(MALLOC_FAIL, 0);
		//printf("While memory allocation\n");
	}	
	//return (!clean_up(err));
	return(0);
}
