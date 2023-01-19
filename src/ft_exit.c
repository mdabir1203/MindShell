
#include "../inc/minishell.h"

void	ft_exit(char **cmd)
{
    if (cmd[1])
    {
        input_message(STR_EXIT_MULTIPLE, 0);
        //printf("Word exit is enough!\n");
    }
    input_message(STR_EXIT_SUCCESSFULL, 0);
    //printf("Exit successfull!\n");
    exit (0);           // where do we want to free our prompt???
}
