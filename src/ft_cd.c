#include "../inc/minishell.h"

void	ft_cd(t_info *info)
{
	char	*path;
	char	*home;
	int		i;

	i = 0;
	home = NULL;
	path = NULL;
	if (info->args[1] == NULL)
	{
		while (info->env[i])
		{
			if (ft_strncmp(info->env[i], "HOME", 4) == 0)
				home = info->env[i];
			i++;
		}
		if (home == NULL)
			return ;
		path = ft_strchr(home, '=');
		path++;
	}
	else
		path = info->args[1];
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		return ;
	}
}