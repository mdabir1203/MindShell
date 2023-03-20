#include "../inc/minishell.h"

void	clean_up_group_structs(t_info *info)
{
	if (!info->groups)
		return ;
	free (info->groups);
	info->groups = NULL;
}

/**
 * @brief free info at last!!!
 */
void	clean_up_info_struct(t_info *info)
{
	if (!info)
		return ;
	free(info);
	info = NULL;
}

void	clean_up_paths(t_info *info)
{
	int		i;
	char	**paths_;

	if (!info->paths)
		return ;
	paths_ = info->paths;
	i = -1;
	while (paths_[++i])
	{
		free(paths_[i]);
	}
	free(paths_);
	paths_ = NULL;
	info->paths = NULL;
}

void	clean_up_prompt(t_info *info)
{
	if (!info->prompt)
		return ;
	free(info->prompt);
	info->prompt = NULL;
}

void	clean_up_env(t_info *info)
{
	char	***env_;
	int		i;
	int		j;

	i = -1;
	env_ = info->env;
	if (!env_)
		return ;
	while (env_[++i])
	{
		j = -1;
		while (env_[i][++j])
		{
			free(env_[i][j]);
			env_[i][j] = NULL;
		}
		free(env_[i]);
		env_[i] = NULL;
	}
	free(env_);
	env_ = NULL;
	info->env = NULL;
}
