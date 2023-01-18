#include "../inc/minishell.h"

void	test_env_vars(t_info *info)
{
	int i = -1;
	int j = -1;
	while (info->env[++i])
	{
		j = -1;
		while (info->env[i][++j])
			printf("%s\n", info->env[i][j]);
		printf("\n");
	}
	printf("paths..----------------------------->>>>>>>>>>>>>\n");
	while (*info->paths)
		printf("%s\n", *info->paths++);
}