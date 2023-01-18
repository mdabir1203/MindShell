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
	return (info);
}