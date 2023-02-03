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

void	test_group(t_info *info)
{
	info->groups->path = "/bin/cat";
	info->groups->arguments = (char **)malloc(sizeof(char *) * 2);
	info->groups->arguments[0] = "infile";
	info->groups->arguments[1] = NULL;
	info->groups->redirect_input_filename = "infile";
	info->groups->redirect_input = REDIR_INPUT;
	// info->groups->redirect_output_filename = "outfile";
	// info->groups->redirect_output = REDIR_OUTPUT;
	info->groups->pipe_out = 1;
	info->groups[1].path = "/bin/cat";
	info->groups[1].arguments = (char **)malloc(sizeof(char *) * 2);
	info->groups[1].arguments[0] = "-e";
	info->groups[1].arguments[1] = NULL;
}

/*Open an infile when "<infile" is presentn and overwrites STDIN*/
void	open_infile(t_group *group)
{
	if (group->redirect_input == REDIR_INPUT)
		group->pipe_in = open(group->redirect_input_filename, O_RDONLY);
	else if (group->redirect_input == REDIR_INPUT_APPEND)
		group->pipe_in = open(group->redirect_input_filename, O_RDONLY);
	if (group->pipe_in < 0)
	{
		perror("open_infile() cannot open file");
		exit(1);
	}
}

/*Makes a pipe and overwrites STDOU with write end, so execve outputs to pipe instead of STDOUT*/
void	open_outfile(t_group *group)
{
	int temp;

	temp = 0;
	if (group->redirect_output == REDIR_OUTPUT)
	{
		temp = open(group->redirect_output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		group->pipe_fd_out[WRITE] = temp;
	}
	else if (group->redirect_output == REDIR_OUTPUT_APPEND)
	{
		temp = open(group->redirect_output_filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		group->pipe_fd_out[WRITE] = temp;
	}
	if (temp < 0)
	{
		perror("could not open outfile");
		exit(1);
	}
}

void	pipe_out(t_group *group)
{
	t_group *temp = group;
	int write;
	int	read;
	
	if (group->pipe_out && !group->redirect_output)
	{
		if (pipe(group->pipe_fd_out) == -1)
		{
			perror("pipe error");
			exit(1);
		}
		if(++temp)
			temp->pipe_fd_in = group->pipe_fd_out;
	}
}

void	execute_exec(t_group *group)
{
	fork_process(group);
	if (group->pid == 0)
	{
		if (group->redirect_input)
			dup_fd(group->pipe_in, 0);
		else if (group->pipe_in > 0)
		{
			close(group->pipe_fd_in[WRITE]);
			dup_fd(group->pipe_fd_in[READ], 0);
		}
		if (group->redirect_output)
			dup_fd(group->pipe_fd_out[WRITE], 1);
		else if (group->pipe_out > 1)
			dup_fd(group->pipe_fd_out[READ], 1);
		if (execve(group->path, group->arguments, NULL) == -1)
		{
			//clean up all structs..??
			perror("exec didnt work\n");
			exit(2);
		}
	}
}

void	executer(t_group	*group)
{
	int status;
	int i;
	
	i = -1;
	//test_group(info);
	printf("num groups %d\n", group->info->num_groups);
	//print_groups(group, group->info); // makes segfault
	while (++i < group->info->num_groups)
	{
		printf("start of group %d\n", group->pipe_in);
		open_infile(group);
		open_outfile(group);
		pipe_out(group);
		if (group->path) //executables
			execute_exec(group);
		// if (group->builtin)
		waitpid(group->pid, &status, 0);
		if (group->pipe_in > 0)
		{
			close(group->pipe_fd_in[READ]);
			close(group->pipe_fd_in[WRITE]);
		}
		printf("END OF LOOP\n");
		if (group->info->num_groups > 1)
			group++;
	}
}