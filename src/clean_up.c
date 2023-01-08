
#include "../inc/minishell.h"

void	clean_up(int clean_up_code)
{
	if (clean_up_code == CTRL_D_PRESSED) 
		exit(0); //should we use rrl_clear_history here to free history? maybe we can check with valgrind? please correct me if i dont understand (nick)
}
