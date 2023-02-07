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
int	open_infile(t_group *group)
{
	if ( group->redirect_input == REDIR_INPUT || group->redirect_input == REDIR_INPUT_APPEND)
	{
		if (group->redirect_input == REDIR_INPUT)
			group->pipe_in = open(group->redirect_input_filename, O_RDONLY);
		else
			group->pipe_in = open(group->redirect_input_filename, O_RDONLY);
		if (group->pipe_in < 0)
		{
			perror("open_infile() cannot open file");
			exit(1);
		}
		return (1);
	}
	return (0);
}

/*Makes a pipe and overwrites STDOU with write end, so execve outputs to pipe instead of STDOUT*/
int	open_outfile(t_group *group)
{
	int temp;

	temp = 0;
	if ( group->redirect_output == REDIR_OUTPUT || group->redirect_output == REDIR_OUTPUT_APPEND)
	{
		if (group->redirect_output == REDIR_OUTPUT)
			group->pipe_fd[WRITE] = open(group->redirect_output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			group->pipe_fd[WRITE] = open(group->redirect_output_filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup_fd(group->pipe_fd[WRITE], 1);
		if (group->pipe_fd[WRITE] < 0)
		{
			perror("could not open outfile");
			exit(1);
		}
		return (1);
	}
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
		printf("executing: %s argument: %s\n", group->path, group->arguments[0]);
		if (execve(group->path, group->arguments, NULL) == -1)
		{
			//clean up all structs..??
			perror("exec didnt work\n");
			exit(2);
		}
	}
	else
		waitpid(group->pid, &status, 0);
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
		printf("bla\n");
		printf("test: %s\n", group[i].arguments[0]);
		if (group[i].pipe_out && !group[i + 1].redirect_input)
			make_pipe(&group[i]);
		//if pipe and no commands then 
		
	printf("after loop\n");
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
	// if (group->pipe_out && !group->redirect_output)
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