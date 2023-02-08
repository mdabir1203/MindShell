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
		printf("dup_func() error\n"),
		exit(1);
	}
}

/*Open an infile when "<infile" is present and overwrites STDIN*/
int	redir_in(t_group *group)
{
	if (group->redir_in == REDIR_INPUT || group->redir_in == REDIR_INPUT_APPEND)
	{
		if (group->redir_in == REDIR_INPUT)
			group->pipe_in = open(group->redir_infile, O_RDONLY);
		else
			group->pipe_in = open(group->redir_infile, O_RDONLY);
		if (group->pipe_in < 0)
		{
			perror("open_infile() cannot open file");
			exit(1);
		}
		return (1);
	}
	dup2(group->pipe_in, 0);
	return (0);
}

/*Makes a pipe and overwrites STDOU with write end, so execve outputs to pipe instead of STDOUT*/
int	redir_out(t_group *group)
{
	if ( group->redir_out == REDIR_OUTPUT || group->redir_out == REDIR_OUTPUT_APPEND)
	{
		if (group->redir_out == REDIR_OUTPUT)
			group->redir_out = open(group->redir_outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			group->redir_out = open(group->redir_outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (group->pipe_fd[WRITE] < 0)
		{
			perror("could not open outfile");
			exit(1);
		}
		return (1);
	}
	dup_fd(group->redir_out, 1);
	return (0);
}

int	make_pipe(t_group *group)
{
	int pipe_fd[2];

	if(pipe(pipe_fd) == -1)
	{
		perror("pipe error");
		exit(1);
	}
	group->pid = fork();
	printf("forked\n");
	if (group->pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	else if (group->pid == 0) //CHILD
	{
		close(pipe_fd[WRITE]);
		dup_fd(pipe_fd[READ], 0);
		return (1);
	}
	else
	{
		close(pipe_fd[READ]);
		dup_fd(pipe_fd[WRITE], 1);
		return (2);
	}
}

void	exec_executables(t_group *group)
{
	int status;

	if (group->arguments) //CHILD
	{
		// group->arguments[0] = "cat";
		// group->arguments[1] = "infile";
		// group->arguments[2] = NULL;
		//printf("executing: %s argument: %s\n", group->path, group->arguments[0]);
		if (execve(group->path, group->arguments, NULL) == -1)
		{
			//clean up all structs..??
			perror("exec didnt work\n");
			exit(2);
		}
	}
	else
		waitpid(group->pid, &status, 0);
	printf("after waitpid id: %d\n", group->pid);
}

int	builtins(t_group *group)
{
	if (group->builtin == CMD_ECHO)//strncmp(group->arguments[0], "echo", 4) == 0)
	{
		// printf("executing echo\n");
		ft_echo(group->arguments);
		return (1);
	}
}

void	executer(t_group	*group)
{
	int i;
	int pipe;
	t_group *temp;
	
	i = -1;
	print_groups(group, group->info);
	while (++i < group->info->num_groups)
	{
		if (group->redir_in) //pipein is higher priority than redirect input
			redir_in(group);
		if (group->redir_out)
			redir_out(group);
		if(group->path)
			exec_executables(group);
		
		// else
		// 	builtins(group);
		// if (group[i].pipe_out && !group[i + 1].redir_in)
		// 	make_pipe(&group[i]);
		// if (group->pipe_in)
		// 	close(group->pipe_in);
		// 	if (group->pipe_out)
		// 		close(group->pipe_out);
		if (group->redir_in)
			close(group->redir_in);
		if (group->redir_out)
			close(group->redir_out);
		printf("after executer cycle\n");
	}
}


//  make_pipe
	// 	if (group->pipe_in)
	// 	{
	// 		close(group->pipe_out
	// 		dup_fd(group->pipe_in, 0);
	// 		close(group->pipe_in);
	// 	}
	// 	if (group->pipe_out)
	// 	{
	// 		dup_fd(group->pipe_out, 1);
	// 		close(group->pipe_out);
	// 	}
	// 	if (execve(group->path, group->arguments, NULL) == -1)
	// 	{
	// 		perror("exec didnt work\n");
	// 		exit(2);
	// 	}
	// }
	// if (group->pipe_out && !group->redir_out)
	// {
	// 	if (pipe(group->pipe_fd))
	// 	{
	// 		perror("pipe error");
	// 		exit(1);
	// 	}
	// 	// close(group->pipe_fd[READ]);
	// 	dup_fd(group->pipe_fd[WRITE], 1);
	// 	// close(group->pipe_fd[WRITE]);
	// 	printf("pipe out\n");
	// 	if(++temp)
	// 	{
	// 		temp->pipe_fd_in[READ] = group->pipe_fd[READ];
	// 		temp->pipe_fd_in[WRITE] = group->pipe_fd[WRITE];
	// 	}
	// }