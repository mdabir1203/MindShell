#include "../inc/minishell.h"

void	wait_and_exit_status(t_group *tmp)
{
	int	exit_status;
	int	i;

	i = -1;
	while (++i < tmp->info->num_groups)
	{
		waitpid(tmp->pid, &exit_status, 0);
		//printf("after waitpid %d\n", exit_status);
		if (exit_status > 0)
			g_exit_status = 1; //could also be g_exit_status = exit_status;
		else
			g_exit_status = 0;
		if (i < tmp->info->num_groups - 1)
			tmp++;
	}
}