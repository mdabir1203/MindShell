#include "../inc/minishell.h"

// void	execute_builtins(t_info	*info)
// {
// 	//find the macro interger and pass param to eg ft_echo
// }

void	fork_process(t_group *group)
{
	group->pid = fork();
	if (group->pid == -1)
	{
		perror("fork error");
		exit(1);
	}
}

void	dup_fd(int	fd_new, int fd_old)
{
	if (dup2(fd_new, fd_old) < 0)
	{
		printf("dup_func() error new %d old %d\n", fd_new, fd_old);
		exit(1);
	}
}

/*Open an infile when "<infile" is present and overwrites STDIN*/
int	redir_in(t_group *group)
{
	if (group->redir_in == REDIR_INPUT || group->redir_in == REDIR_INPUT_APPEND)
	{
		if (group->redir_in == REDIR_INPUT)
			group->redir_in = open(group->redir_infile, O_RDONLY);
		else
			group->redir_in = open(group->redir_infile, O_RDONLY);
		if (group->redir_in < 0)
		{
			perror("open_infile() cannot open file");
			exit(1);
		}
		return (1);
	}
	return (0);
}

/*Makes a pipe and overwrites STDOU with write end, so execve outputs to pipe instead of STDOUT*/
int	redir_out(t_group *group)
{
	if ( group->redir_out == REDIR_OUTPUT || group->redir_out == REDIR_OUTPUT_APPEND)
	{
		if (group->redir_out == REDIR_OUTPUT)
		{
				group->redir_out = open(group->redir_outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		}
		else
			group->redir_out = open(group->redir_outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (group->redir_out < 0)
		{
			perror("could not open outfile");
			exit(1);
		}
		return (1);
	}
	return (0);
}

void	make_pipe(t_group *group)
{
	//------------------pipe------------------
	if(pipe(group->pipe_fd) == -1)
	{
		perror("pipe error");
		exit(1);
	}
}

void	replace_pipe_in_next_group(t_group *group, int new_pipe_in)
{
	t_group *temp;

	temp = group;
	temp++;
	temp->pipe_in = new_pipe_in;
}

int	next_have_pipe_out(t_group *group)
{
	t_group *temp;

	temp = group;
	temp++;
	if (temp->pipe_out)
		return (1);
	return (0);
}

void	exec_executables(t_group *group)
{
	int status;

	fork_process(group);
	if (group->pid == 0)
	{
		//-------INPUT-----------------------------------
		if (group->redir_in)
		{
			if (group->pipe_in)
				close (group->pipe_in);
			dup_fd(group->redir_in, 0);
		}
		else if (group->pipe_in)
			dup_fd(group->pipe_in, 0);
		//-------OUTPUT-----------------------------------
		if (group->redir_out)
			dup_fd(group->redir_out, 1);
		else if (group->pipe_out)
			dup_fd(group->pipe_fd[WRITE], 1);
		if (execve(group->path, group->arguments, NULL) == -1)
		{
			close(group->pipe_fd[WRITE]);
			close(group->pipe_fd[READ]);
			perror("exec didnt work\n");
			//clean up all structs..??
			exit(2);
		}
	}
	else
	{
		waitpid(group->pid, &status, 0);
		// if (group->pipe_out && !next_have_pipe_out(group))
		// 	close(group->pipe_fd[WRITE]);
		// if (group->pipe_in)
		//  	close(group->pipe_fd[READ]);
		if (group->pipe_out)
			close(group->pipe_fd[WRITE]);
		// if (group->pipe_in && !group->redir_in)
		// 	close(group->pipe_in);
		//manual setting of pipe_in for next group
		if (group->pipe_out && !group->redir_out)
			replace_pipe_in_next_group(group, group->pipe_fd[READ]);
		else if (group->pipe_out && group->redir_out)
			replace_pipe_in_next_group(group, 0);
	}
	printf("after waitpid id: %d\n", group->pid);
}

int	builtins(t_group *group)
{
	if (group->builtin == CMD_ECHO)//strncmp(group->arguments[0], "echo", 4) == 0)
	{
		//printf("executing echo\n");
		ft_echo(group->arguments, group->pipe_out);
		return (1);
	}
	return (0); // is that ok Nick?
}

void	executer(t_group	*group)
{
	int i;
	
	i = -1;
	print_groups(group, group->info);
	while (++i < group->info->num_groups)
	{
		if (!input_error_check(group->info, group))
		{
			printf("inside2\n");
			break;
		}
		if (group->redir_in)
			redir_in(group);
		if (group->redir_out)
			redir_out(group);
		//pipe if no redirections and pipe out is present
		if (group->pipe_out && !group->redir_out && !group->redir_in)
			make_pipe(group); //maybe change pipe_in
		printf("cycle befor exec:  %d path %s pipe in = %d\n", i, group->arguments[0], group->pipe_in);
		if(group->path)
			exec_executables(group);
		// else
		// 	builtins(group);

		if (i < group->info->num_groups - 1) //increment group pointer
			group++;
	}
	// close(0);
	// close(1);
	// close(2);
}
