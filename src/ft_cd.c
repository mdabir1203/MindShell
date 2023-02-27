#include "../inc/minishell.h"

int	slash_at_end(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == '/')
		return (1);
	return (0);
}

/**
 * @brief gets a path
 * decides if that path is relative, absolute or ~/
 * there can be a '/' or not in path
 * 
 * @return malloced space with the name inside
 * if couldn't malloc returns NULL
 * return a path without / at the end
 */
char *get_absolute_path(char *path, t_info *info) // test path with " kdsjf/  "
{
	char	*new_wd;
	char	*buf;

	buf = NULL;	
	if (!path)
	{
		new_wd = value_of_variable_from_env(info->env, "HOME", 4);
		new_wd = ft_strdup(new_wd);
		if (!new_wd)
			return (NULL);
	}
	// else if (*path == '~')
	// {

	// }
	else if (*path == '/')
	{
		new_wd = ft_strdup(path);
		if (slash_at_end(new_wd))
			new_wd[ft_strlen(new_wd) - 1] = '\0';
	}
	else
	{
		new_wd = getcwd(NULL, 0);
		buf = ft_strjoin(new_wd, "/");
		free (new_wd);
		new_wd = ft_strjoin(buf, path);
		free(buf);
		if (slash_at_end(new_wd))
			new_wd[ft_strlen(new_wd) - 1] = '\0';
	}
	return (new_wd);
}

/**
 * @brief expects and 2d array of strings{"cd", "/somedir", "not important"...}
 * only takes argument one as the new path
 * 
 * Decide if argument is a absolut path, a relative path or an ~/path
 * get the absolute path
 * 
 * check if the path is available
 * put the actual path to OLDPWD in env
 * change to new path with
 * put the new path to PWD in env
 * 
 */
void	ft_cd(char **args, t_info *info)
{
	char	*absolute_path;

	// absolute_path = get_absolute_path(args[1], info);
	chdir(args[1]);
	printf("%s\n", getcwd(NULL, 0));// absolute_path);
	// char	*path;
	// char	*home;
	// int		i;

	// i = 0;
	// home = NULL;
	// path = NULL;
	// if (info->args[1] == NULL)
	// {
	// 	while (info->env[i])
	// 	{
	// 		if (ft_strncmp(info->env[i], "HOME", 4) == 0)
	// 			home = info->env[i];
	// 		i++;
	// 	}
	// 	if (home == NULL)
	// 		return ;
	// 	path = ft_strchr(home, '=');
	// 	path++;
	// }
	// else
	// 	path = info->args[1];
	// if (chdir(path) == -1)
	// {
	// 	printf("cd: %s: No such file or directory\n", path);
	// 	return ;
	// }
}