#include "../inc/minishell.h"

void	populate_var(char *str, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '=')
	{
		str[i] = arg[i];
		i++;
	}
}

void	populate_cont(char *str, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (arg[i] != '=')
		i++;
	while (arg[++i])
	{
		str[++j] = arg[i];
	}
}

void	export_with_no_args(t_info *info)
{
	int	i;

	i = -1;
	while (info->env[++i])
		printf("declare -x %s=\"%s\"\n", info->env[i][0], info->env[i][1]);
}

/**
 * @brief expects something like ab=cd as arg
 * @return the position in the env array of arg (array starts with 0),
 *  if no return -1
 */
int	var_pos_in_env_export(char *arg, char ***env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i][0], arg, num_var_chars(arg)) &&
			env[i][0][num_var_chars(arg)] == '\0')
			return (i);
	}
	return (-1);
}

/**
 * @brief 
 * buf old content
 * malloc memory for the content into env ptr at the right spot
 * copy content
 * free the old content
 * and set the new info->paths if necessary
 */
void	replace_cont_of_var(char *arg, char ***env, t_info *info)
{
	char	*buf;
	int		var_pos_in_env;

	var_pos_in_env = var_pos_in_env_export(arg, env);
	buf = env[var_pos_in_env][1];
	env[var_pos_in_env][1] = ft_calloc(num_cont_chars(arg) + 1, sizeof(char));
	populate_cont(env[var_pos_in_env][1], arg);
	free (buf);
	if (!ft_strncmp(arg, "PATH=", 5))
	{
		clean_up_paths(info);
		info->paths = ft_split((arg + 5), ':');
	}
}
