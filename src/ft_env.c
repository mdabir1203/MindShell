#include "../inc/minishell.h"

void	ft_env_sub(t_info *info)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (info->env[++i])
	{
		j = -1;
		while (info->env[i][++j])
		{
			k = -1;
			while (info->env[i][j][++k])
				write(1, &info->env[i][j][k], 1);
			if (j == 0)
				write(1, "=", 1);
		}
		printf("\n");
	}
}

void	ft_env(t_info *info)
{
	int	argc;

	argc = 0;
	while (info->groups->arguments[argc])
		argc++;
	if (argc > 1)
	{
		printf("env: %s No such file or directory\n", \
			info->groups->arguments[1]);
		exit (1);
	}
	ft_env_sub(info);
}

	// while (info->env[++i])
	// {
	// 	j = -1;
	// 	while (info->env[i][++j])
	// 	{
	// 		k = -1;
	// 		while (info->env[i][j][++k])
	// 			write(1, &info->env[i][j][k], 1);
	// 		if (j == 0)
	// 			write(1, "=", 1);
	// 	}
	// 	printf("\n");
	// }
