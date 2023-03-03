
#include "../inc/minishell.h"

void	ft_exit(t_info *info)
{
    if (info->input_lexer[1])
    {
        input_message(STR_EXIT_MULTIPLE, 0);
        //printf("Word exit is enough!\n");
    }
    input_message(STR_EXIT_SUCCESSFULL, 0);
    //printf("Exit successfull!\n");
		clean_up(CLEAN_UP_FOR_NEW_PROMPT, info);
		clean_up(CLEAN_UP_REST_BEFORE_EXIT, info);
    exit (0);           // where do we want to free our prompt???
}
