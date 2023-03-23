#include "../inc/minishell.h"

void	fork_process(t_group *group)
{
	group->pid = fork();
	if (group->pid == -1)
	{
		perror("fork error");
		g_exit_status = 1;
		exit(1);
	}
}

void	fds_and_pipe_after_execve(t_group *group)
{
	if (group->pipe_out)
		close(group->pipe_fd[WRITE]);
	if (group->pipe_in)
		close(group->pipe_in);
	if (group->pipe_out && !group->redir_out)
		replace_pipe_in_next_group(group, group->pipe_fd[READ]);
	else if (group->pipe_out && group->redir_out)
		replace_pipe_in_next_group(group, 0);
}

void	fork_and_execve(t_group *group)
{
	fork_process(group);
	if (group->pid == 0)
	{
		handle_redir_and_dup(group);
		if (group->builtin == CMD_ECHO || group->builtin == CMD_ENV \
		|| group->builtin == CMD_PWD)
			builtins_with_output(group);
		else if (group->path)
		{
			if (execve(group->path, group->arguments, NULL) == -1)
			{
				g_exit_status = 1; //not needeed whole bracket?
				perror("exec didnt work\n");
			}
		}
		clean_up(CTRL_D_PRESSED, group->info);
		exit(0);
	}
	else
		fds_and_pipe_after_execve(group);
}

void	piping_builtin_and_exec(t_group *group)
{
	if (group->pipe_out)
		make_pipe(group);
	if (group->builtin == CMD_EXPORT || group->builtin == CMD_UNSET \
		|| group->builtin == CMD_EXIT || group->builtin == CMD_CD || group->builtin == CMD_CLEAR)
			builtin_no_piping(group);
	else if (group->path || group->builtin || group->redir_out)
		fork_and_execve(group);
}

void	executer(t_group	*group)
{
	int		i;
	t_group	*tmp;

	tmp = group;
	i = -1;
	//print_groups(group, group->info);
	while (++i < group->info->num_groups)
	{
		g_exit_status = 0; //should not be like this
		if (!group->builtin && !group->path)
		{
			input_message(STR_WRITE_ERROR, 0);
			group->exit_status = 127;
			if (group->pipe_out)
				replace_pipe_in_next_group(group, 0);
			if (i < group->info->num_groups - 1)
				group++;
			continue ;
		}
		if (!check_access_infile_outfile(group))
			break ;
		piping_builtin_and_exec(group);
		if (i < group->info->num_groups - 1)
			group++;
	}
	wait_and_exit_status(tmp);
}
