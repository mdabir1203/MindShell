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

void	p2d(char **ptr)
{
	printf("Start Content of **ptr: %p\n", ptr);
	printf("Content of *ptr: %p\n", *ptr);
	int i = -1;
	while(ptr[++i])
	{
		printf("%p : _%s_\n", ptr[i], ptr[i]);

	}
	printf("%p\n", ptr[i]);
}