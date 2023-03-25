#include "../inc/minishell.h"

// where do we want to free our prompt???
//printf("Word exit is enough!\n");
void	ft_exit(t_info *info)
{
	if (info->input_lexer[1])
		input_message(STR_EXIT_SUCCESSFULL, 2);
	clean_up(CLEAN_UP_FOR_NEW_PROMPT, info);
	clean_up(CLEAN_UP_REST_BEFORE_EXIT, info);
	exit (0);
}
