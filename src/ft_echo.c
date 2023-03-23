#include "../inc/minishell.h"

/*
* shortens ft_echo function < 25 lines.
*/
void	ft_echo_helper(char **args, int arg_j)
{
	while (args[++arg_j])
	{
		ft_putstr_fd(args[arg_j], 1);
		ft_putchar_fd(' ', 1);
	}
}

/*
* -n without the \n
*/
void	ft_echo(char **args, int pipe_out)
{
	int	arg_j;

	arg_j = 0;
	if (!args[1])
	{
		if (!(pipe_out == 1) || args[1])
			ft_putchar_fd('\n', 1);
	}
	else if (!ft_strncmp(args[1], "-n", 2))
	{
		++arg_j;
		ft_echo_helper(args, arg_j);
		ft_putstr_fd("\b", 1);
	}
	else
	{
		ft_echo_helper(args, arg_j);
		if (!(pipe_out == 1) || args[arg_j])
			ft_putchar_fd('\n', 1);
	}
}
