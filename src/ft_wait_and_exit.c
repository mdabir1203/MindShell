#include "../inc/minishell.h"

void	wait_and_exit_status(t_group *tmp)
{
	int	exit_status;
	int	i;

	i = -1;
	while (++i < tmp->info->num_groups)
	{
		if ((tmp->path || tmp->builtin == CMD_ECHO || tmp->builtin == CMD_ENV \
		|| tmp->builtin == CMD_PWD) && tmp->exit_status == 0)
		{
			waitpid(tmp->pid, &exit_status, 0);
			if (exit_status > 0)
				g_exit_status = 1;
			else
				g_exit_status = 0;
		}
		else
			g_exit_status = tmp->exit_status;
		if (i < tmp->info->num_groups - 1)
			tmp++;
	}
}
