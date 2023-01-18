#include "../inc/minishell.h"

int	check_and_store(char *slash_added, char *slash_not_added, char *cmd, t_info *t_info)
{
	if (!access(slash_added, X_OK))
	{
		t_info->root_cmd = ft_strdup(slash_added);
		return (1);
	}
	if (!access(slash_not_added, X_OK))
	{
		t_info->root_cmd = ft_strdup(slash_not_added);
		return (1);
	}
	if (!access(cmd, X_OK))
	{
		t_info->root_cmd = ft_strdup(cmd);
		return (1);
	}
	return (0);
}

char	*add_slash(char *cmd, char *path)
{
	char *slash_added;
	char *temp;

	temp = ft_strjoin(path, "/");
	slash_added = ft_strjoin(temp, cmd);
	free(temp);
	return (slash_added);
}

int	is_an_executable(char *cmd, t_info *t_info)
{
	int i;
	char *slash_added;
	char *slash_not_added;

	i = -1;
	while (t_info->paths[++i])
	{
		slash_added = add_slash(cmd, t_info->paths[i]);
		slash_not_added = ft_strjoin(slash_added, cmd);
		if (check_and_store(slash_added, slash_not_added, cmd, t_info))
		{
			t_info->nb_root_cmd++;
			free(slash_added);
			free(slash_not_added);
			return (1);
		}
		free(slash_added);
		free(slash_not_added);
	}
	return (0);
}
