#include "../inc/minishell.h"

void ft_env(t_info *info)
{
	int i;
	int j;
	int k;

	i = -1;
	while (info->env[++i])
	{
		j = -1;
		while (info->env[i][++j])
		{
			k = -1;
			while(info->env[i][j][++k])
				write(1, &info->env[i][j][k], 1);
			if (j == 0)
				write(1, "=", 1); //print = after first char
		}
		printf("\n");
	}
}
