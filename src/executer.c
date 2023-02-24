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
			clean_up(CLEAN_UP_FOR_NEW_PROMPT, group->info); //is this nessecary?
			exit(2);
		}
		dup_fd(group->redir_in, 0);
		close(group->redir_in);
	}
	return (1);
}

/*Makes a pipe and overwrites STDOU with write end, so execve outputs to pipe instead of STDOUT*/
void	redir_out(t_group *group) //make remove return of int
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
			exit(0);
		}
		dup_fd(group->redir_out, 1);
		close(group->redir_out);
	}
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

void	closing_fds(t_group *group)
{
	if (group->redir_out)
			close(group->redir_out);
	if(group->redir_in)
		close(group->redir_in);
	if (group->pipe_in)
		close(group->pipe_in);
	if (group->pipe_out)
	{
		close(group->pipe_fd[READ]);
		close(group->pipe_fd[WRITE]);
	}
}

void ft_env(t_info *info)
{
	int i;
	int j;

	i = -1;
	while (info->env[++i])
	{
		j = -1;
		while (info->env[i][++j])
		{
			printf("%s", info->env[i][j]);
			if (j == 0)
				printf("="); //print = after first char
		}
		printf("\n");
	}
}

void	builtins(t_group *group)
{
	if (group->builtin == CMD_ECHO)//strncmp(group->arguments[0], "echo", 4) == 0)
		ft_echo(group->arguments, group->pipe_out);
	else if (group->builtin == CMD_EXIT)
		ft_exit(group->info);
	// else if (group->builtin == CMD_PWD)
	// 	ft_pwd();
	else if (group->builtin == CMD_EXPORT)
		ft_export(group->arguments, group->info);
	else if (group->builtin == CMD_UNSET)
		ft_unset(group->arguments, group->info);
	else if (group->builtin == CMD_ENV)
		ft_env(group->info);
	// else if (group->builtin == CMD_CD)
		//needs to be filled in
	_Exit(3);
}

void	exec_executables(t_group *group)
{
	fork_process(group); //2 PROCESSES
	if (group->pid == 0)
	{
		//-------INPUT-----------------------------------
		if (group->redir_in)
			redir_in(group); //HERE i open files
		else if (group->pipe_in)
			dup_fd(group->pipe_in, 0); //READ end from prev pipe
		//-------OUTPUT-----------------------------------
		if (group->redir_out) //HERE i open files
			redir_out(group);
		else if (group->pipe_out)
			dup_fd(group->pipe_fd[WRITE], 1);
		//-------CLOSING-----------------------------------
		 closing_fds(group);
		//-------EXECVE-----------------------------------
		if(group->builtin)
			builtins(group);
		else if (execve(group->path, group->arguments, NULL) == -1)
		{
			closing_fds(group);
			perror("exec didnt work\n");
			//clean up all structs..??
			exit(2);
		}
	}
	else
	{
		//ONLY HANDLE PIPES FROM CURR AND PREV
		if (group->pipe_out)
			close(group->pipe_fd[WRITE]); //for sure
		if (group->pipe_in)
			close(group->pipe_in);
		if (group->pipe_out && !group->redir_out)
			replace_pipe_in_next_group(group, group->pipe_fd[READ]);
		else if (group->pipe_out && group->redir_out)
			replace_pipe_in_next_group(group, 0);
	}
}


void	executer(t_group	*group)
{
	int i;
	
	i = -1;
	print_groups(group, group->info);
	//ft_env(group->info); //for testing
	while (++i < group->info->num_groups)
	{
		if (!executer_error_check(group->info, group))
		{
			//printf("inside2\n");
			break;
		}
		//pipe if no redirections and pipe out is present
		if (!group->redir_out && group->pipe_out)
		{
			printf("pipe is made, i = %d \n", i);
			make_pipe(group);
		}
		printf("i = %d arg[0] %s pipe in = %d\n", i, group->arguments[0], group->pipe_in);
		if(group->path || group->builtin)
			exec_executables(group);
		if (i < group->info->num_groups - 1) //increment group pointer
			group++;
	}
	while (wait(NULL) > 0)
		;
}
