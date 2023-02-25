#include "../inc/minishell.h"

/*
Saves all environment variables in a 3d array
*/
void	make_env(char **envp, t_info *info)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	if(!(info->env = malloc(sizeof(char *) * i + 1)))
		exit (0);
	info->env[i] = NULL;
	while (--i >= 0)
	{
		info->env[i] = ft_one_split(envp[i], '=');
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			info->paths =  ft_split(envp[i] + 5, ':');
	}
}
