#include "../inc/minishell.h"

/**
 * @brief return 0 if everything worked out
 */
int make_prompt(t_info *info)
{
	info->prompt = NULL;
	return (0);
}


t_info	*init(char **envp)
{
	t_info *info;
	info = malloc(sizeof(t_info)); //need to clean up 
	make_env(envp, info);
	make_prompt(info);
	info->input_lexer = NULL;
	return (info);
}

t_group *init_groups(t_info *info) // init everything inside to NULL
{
	t_group *groups;
	int i;

	i = -1;
	if (!(groups = malloc(sizeof(*groups) * info->num_groups))) 
	{
		error(ERR_MALLOC_INIT_GROUPS, info);
		return (NULL);
	}
	//save malloc
	//groups[info->num_groups] = NULL;
	while (++i < info->num_groups)
	{
		//groups[i] = malloc(sizeof(t_group)); // write clean_up
		//save malloc
		groups[i].path = NULL;
		groups[i].redirect_input = 0;
		groups[i].redirect_input_filename = NULL;
		groups[i].redirect_output = 0;
		groups[i].redirect_output_filename = NULL;
		groups[i].pipe_in = 0;
		groups[i].pipe_out = 0;
	}
	printf("ptr %d\n",  groups[0].redirect_output);
	return (groups);
}