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
void	print_groups(t_group *groups, t_info *info)
{
	int i = -1;
	int j;
	printf("num groups %d\n", groups->info->num_groups);
	while (++i < info->num_groups)
	{
		j = -1;
		printf("\n\t\t\t\tGROUP %d\n", i);
		while (groups[i].arguments[++j])
			printf("\targument %d:\t_%s_\n", j, groups[i].arguments[j]);
		printf("\targument %d:\t_%s_\n", j, groups[i].arguments[j]);
		printf("path: \t\t\t\t_%s_\n", groups[i].path);
		printf("builtin: \t\t\t_%d_\n", groups[i].builtin);
		printf("redirect_input: \t\t_%d_\n", groups[i].redirect_input);
		printf("redirect_input_filename: \t_%s_\n", groups[i].redirect_input_filename);
		printf("redirect_output: \t\t_%d_\n", groups[i].redirect_output);
		printf("redirect_output_filename:\t_%s_\n", groups[i].redirect_output_filename);
		// printf("argument_filename\t_%s_\n\n", groups[i].argument_filename);
		printf("pipe_in: \t\t_%d_\n", groups[i].pipe_in);
		printf("pipe_out: \t\t_%d_\n\n", groups[i].pipe_out);
		printf("\n");
	}
	// printf("Last group pointer %p\n", &groups[i]);
}
