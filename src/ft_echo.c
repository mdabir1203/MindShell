
#include "../inc/minishell.h"

void	ft_echo(t_group *groups, t_parse_lexer *pl)
{
	int arg_j;

	arg_j = -1;
	while (groups[pl->act_group].arguments[++arg_j])
	{
		ft_putstr_fd(groups[pl->act_group].arguments[arg_j], 1);
		ft_putchar_fd(' ', 1);
		//printf("arg_j %d", arg_j);
	}
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
