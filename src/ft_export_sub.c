#include "../inc/minishell.h"

/**
 * @return num of arguments minus one, because the first argument
 * is the command itself
 */
int	num_args(char **args)
{
	int	num;

	num = 0;
	while (*args)
	{
		args++;
		num++;
	}
	return (num - 1);
}

int	num_env_args(char ***args)
{
	int	num;

	num = 0;
	while (*args)
	{
		args++;
		num++;
	}
	return (num);
}

void	populate_new_env_with_old_args(char ***new_env, char ***old_env)
{
	while (*old_env)
	{
		*new_env = *old_env;
		new_env++;
		old_env++;
	}
}

int	num_var_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

int	num_cont_chars(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] != '=')
		i++;
	while (str[++i])
		j++;
	return (j);
}
