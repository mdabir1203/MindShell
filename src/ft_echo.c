
#include "../inc/minishell.h"

// -n without the \n
void	ft_echo(char	**args, int pipe_out)
{
	int arg_j;

	arg_j = 0;
	//printf("pipe out %d\n", pipe_out);
	if (!strncmp(args[1], "-n", 2))
	{
		++arg_j;
		while (args[++arg_j])	// starting from 1 as 0 is the command itself
		{
			ft_putstr_fd(args[arg_j], 1);
			ft_putchar_fd(' ', 1);
		}
		ft_putstr_fd("\b", 1);
	}
	else
	{
		while (args[++arg_j])	// starting from 1 as 0 is the command itself
		{
			ft_putstr_fd(args[arg_j], 1);	// counting 
			ft_putchar_fd(' ', 1);
		}
		if (args[arg_j] || !(pipe_out == 1))	// doesn't give an empty line for "echo" without args anymore
			ft_putchar_fd('\n', 1);
	}
}
