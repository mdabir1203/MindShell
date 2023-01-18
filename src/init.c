#include "../inc/minishell.h"

/**
 * @brief return 0 if everything worked out
 */
int make_prompt(t_info *info)
{
	info->prompt = NULL;
	return (0);
}

/**
 * @brief return 0 if everything worked out
 */
int init_envp(t_info *info)
{
	info->env = NULL;
	return (0);
}


t_info	*init()
{
	t_info *info;
	info = malloc(sizeof(t_info)); //need to clean up 
	make_prompt(info);
	init_envp(info);
	return (info);
}