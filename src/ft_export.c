#include "../inc/minishell.h"

/**
 * @brief looks for a '=' sign in every argument
 * start at i = 0 because first argument is export
 * @returns 0 if everything is ok, 1 if at least one arg 
 * has no '=' or invalid identifier
 * besides the first one (that is "export")
 */
int	error_check_export(char **args)
{
	int	equal_flag;
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		equal_flag = 0;
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '=')
				equal_flag = 1;
			if (!equal_flag && !(ft_isalnum(args[i][j]) || args[i][j] == '_'))
			{
				input_message(INVALID_IDENTIFIER, 0);
				return (1);
			}
		}
		if (equal_flag == 0)
			return (1);
	}
	return (0);
}

int	export_while(char ***env_buf, int i, char **args, t_info *info)
{
	env_buf[i] = malloc(sizeof(char *) * 3);
	if (!env_buf[i])
		return (2);
	env_buf[i][2] = NULL;
	env_buf[i][0] = ft_calloc((num_var_chars(*args) + 1), sizeof(char));
	if (!env_buf[i][0])
		return (2);
	env_buf[i][1] = ft_calloc((num_cont_chars(*args) + 1), sizeof(char));
	if (!env_buf[i][1])
		return (2);
	populate_var(env_buf[i][0], *args);
	populate_cont(env_buf[i][1], *args);
	if (!ft_strncmp(*args, "PATH=", 5))
		info->paths = ft_split((*args + 5), ':');
	return (0);
}

/**
 * @brief helper function for ft_export
 * checks if the command is only "export" -> print out:
 * declare -x .....
 * 
 * counts how many arguments after the first argument "export" there are
 * 
 * checks for errors -> every argument has to have a "=" and correct identifiers
 * these are alpha num chars and "_"
 *
 * gets memory for a new env array including the new arguments
 * populates the new array and frees the old one
 * 
 * @return 0 and 2 should also be returned of ft_export
 * return value of 1 means ft_export can go on
 */
int	ft_export_sub(char **args, int *num_new_args, \
	t_info *info, char ****env_buf)
{
	if (!args[1])
		export_with_no_args(info);
	*num_new_args = num_args(args);
	if (*num_new_args == 0)
		return (0);
	if (error_check_export(args))
		return (0);
	*env_buf = info->env;
	info->env = ft_calloc((num_env_args(info->env) + *num_new_args + 1), \
		sizeof(char *));
	if (!info->env)
		return (2);
	populate_new_env_with_old_args(info->env, *env_buf);
	free (*env_buf);
	*env_buf = info->env;
	return (1);
}

int	env_buf_end(char ***env_buf)
{
	int	i;

	i = -1;
	while (env_buf[++i])
		;
	return (i);
}

/**
 * @brief I am sorry for the ugly refactoring of this function
 * give it a 2D char array -> arguments 
 * in the form of:{"export", "some_variable_name=some_content", 
 * "2ndvar=second_content", NULL}
 * It takes the info->env and makes it bigger (the first array)
 * 
 * how many arguments do we have?
 * // how many arguments did we already find in the env - don't do this
 * calloc space for the array of ptrs to the environment variables 
 * // - num that we already found - don't do this
 * plus the new ones + zeros at the end
 * copy old ptrs to the new space, free the old array
 * step one argument forward, because the first one is "export"
 * search the end of the environment variables
 * while loop through the new args
 * 	if there is already a variable with that name in env
 * 	then replace the content of that var
 * 	everything after here is in export_while()
 * 		malloc memory for an array of 3; [2] is (NULL)
 * 		with its ptr at the end of env
 * 		malloc memory for the variable name of 
 * 		the first argument -> put its ptr to env[i][0]
 * 		the same for the content
 * 		copy variable name into malloced memory 
 * 		-> populate_var()
 * 		same for content
 * @return 0 for sucess, but also 0 from ft_export_sub 
 * from error check (not good), 2 for malloc error
 */
int	ft_export(char **args, t_info *info)
{
	int		num_new_args;
	char	***env_buf;
	int		i;
	int		ret_ex_sub;

	num_new_args = 0;
	ret_ex_sub = ft_export_sub(args, &num_new_args, info, &env_buf);
	if (ret_ex_sub != 1)
		return (ret_ex_sub);
	i = env_buf_end(env_buf);
	args++;
	while (*args)
	{
		if (var_pos_in_env_export(*args, info->env) != -1)
		{
			replace_cont_of_var(*args, info->env, info);
			args++;
			continue ;
		}
		if (export_while(env_buf, i, args, info) == 2)
			return (2);
		args++;
		i++;
	}
	return (0);
}
