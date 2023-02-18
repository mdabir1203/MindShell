
#include "../inc/minishell.h"

void	ft_echo(char	**args)
{
	int arg_j;

	arg_j = 0;
	while (args[++arg_j])	// starting from 1 as 0 is the command itself
	{
		ft_putstr_fd(args[arg_j], 1);	// counting 
		ft_putchar_fd(' ', 1);
		//printf("arg_j %d", arg_j);
	}
	if (args[arg_j])
		ft_putchar_fd('\n', 1);
}

// -n without the \n
/*void	ft_echo(char **cmd)
{
	int i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd[i])
	{
		if (!strncmp(cmd[i], "-n", 3))
		{
			i++;
			flag = 1;
		}
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i+1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag == 1)
		ft_putchar_fd('%', 1);
	ft_putchar_fd('\n', 1);
}*/
