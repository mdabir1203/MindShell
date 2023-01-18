#include "../inc/minishell.h"


/*
Gets PATH from environment, and splits it into an array of paths
*/
void	malloc_paths_from_env(char **envp, t_info *info)
{
	int i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			info->paths =  ft_split(envp[i] + 5, ':');
			return ;
		}
	}
	exit (0);
}

/*
Saves all environment variables in a 3d array
*/
void	make_env(char **envp, t_info *info)
{
	int i;

	i = -1;
	while (envp[++i]);
	if(!(info->env = malloc(sizeof(char *) * i + 1)))
		exit (0);
	info->env[i] = NULL;
	while (--i >= 0)
		info->env[i] = ft_one_split(envp[i], '=');

	malloc_paths_from_env(envp, info);
}
