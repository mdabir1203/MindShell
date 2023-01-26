
#include "../inc/minishell.h"

void	clean_up_groups(t_info *info)
{
	free(info->groups);

}

void	clean_up(int clean_up_code, t_info *info)
{
	if (clean_up_code == CTRL_D_PRESSED) 
		exit(0); //should we use rrl_clear_history here to free history? maybe we can check with valgrind? please correct me if i dont understand (nick)
	if (clean_up_code == ERR_MALLOC_INIT_GROUPS)
	{
		clean_up_groups(info);
	}
	
	return;
}
