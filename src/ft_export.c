#include "../inc/minishell.h"

/**
 * @return num of arguments minus one, because the first argument
 * is the command itself
 */
int	num_args(char **args)
{
	int num;

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
	int num;

	num = 0;
	while (*args)
	{
		args++;
		num++;
	}
	return (num);
}

void	populate_new_env(char ***new_env, char ***old_env)
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
	int i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}
int	num_cont_chars(char *str)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i] != '=')
		i++;
	while (str[++i])
		j++;
	return (j);
}

void populate_var(char *str, char *arg)
{
	int i;

	i = 0;
	while (arg[i] != '=')
	{
		str[i] = arg[i];
		i++;
	}
}

void populate_cont(char *str, char *arg)
{
	int i;
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

/**
 * @brief looks for a '=' sign in every argument
 * start at i = 0 because first argument is export
 * @returns 0 if everything is ok, 1 if at least one arg has no '=',
 * besides the first one (that is "export")
 */
int	error_check(char **args)
{
	int equal_flag; 
	int i;
	int j;

	i = 0;
	while (args[++i])
	{
		equal_flag = 0;
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '=')
				equal_flag = 1;
		}
		if (equal_flag == 0)
			return (1);
	}
	return (0);
}

/**
 * @brief give it a 2D char array -> arguments 
 * in the form of:{"export", "some_variable_name=some_content", "2ndvar=second_content", NULL}
 * It takes the info->env and makes it bigger (the first array)
 * 
 * how many arguments do we have?
 * calloc space for the array of ptrs to the environment variables plus the new ones + zeros at the end
 * copy old ptrs to the new space, free the old array
 * step one argument forward, because the first one is "export"
 * search the end of the environment variables
 * while loop through the new args
 * 		malloc memory for an array of 3; [2] is (NULL)
 * 		with its ptr at the end of env
 * 		malloc memory for the variable name of 
 * 		the first argument -> put its ptr to env[i][0]
 * 		the same for the content
 * 		copy variable name into malloced memory 
 * 		-> populate_var()
 * 		same for content
 * 		
 * @return 0
 */
int	ft_export(char **args) // export sjkdfh without = sign??
{
	int	num_new_args;
	char	***env_buf;
	int	i;

	num_new_args = num_args(args);
	if (num_new_args == 0)	
		return (0);
	if (error_check(args))
		return (error(ERR_NO_EQUAL_IN_EXPORT_ARG, NULL));
	i = 0;
	env_buf = g_info->env;
	g_info->env = ft_calloc((num_env_args(g_info->env) + num_new_args + 1), sizeof(char *));
	if (!g_info->env)
		return (0); // save really please !!!
	populate_new_env(g_info->env, env_buf);
	free (env_buf);
	env_buf = g_info->env;
	args++;
	while (env_buf[i])
			i++;
	while (*args) // I expect it to have an = sign
	{
		env_buf[i] = malloc(sizeof(char *) * 3);
		env_buf[i][2] = NULL;
		// save malloc!!
		env_buf[i][0] = ft_calloc((num_var_chars(*args) + 1), sizeof(char));
		env_buf[i][1] = ft_calloc((num_cont_chars(*args) + 1), sizeof(char));
		populate_var(env_buf[i][0], *args);
		populate_cont(env_buf[i][1], *args);
		args++;
		i++;
	}
	return (0);
}