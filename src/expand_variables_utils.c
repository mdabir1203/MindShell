#include "../inc/minishell.h"

// Delimiter for Variables
int	var_delimiter(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (0);
	return (1);
}

/**
 * @brief Looks how many chars the variable has 
 * First char is $, so jump that (i = 1)
 * @return returns num of chars of the variable
 * ($var -> returns 3)
 */
int	variable_name_count(char *str)
{
	int	i;

	if (str[1] == '?')
		return (1);
	i = 1;
	while (!var_delimiter(str[i]))
		i++;
	return (i - 1);
}

char	*exit_status(void)
{
	char	*value;

	value = ft_itoa(g_exit_status);
	if (!value)
		return (NULL);
	return (value);
}

/**
 * @return char* with malloced memory with the string inside
 */
char	*value_of_variable_from_env(char ***env, char *var, int len)
{
	int		i;
	char	*value;

	i = -1;
	if (*var == '?')
		return (exit_status());
	while (env[++i])
	{
		if (!ft_strncmp(var, env[i][0], len + 1))
		{
			value = ft_strdup(env[i][1]);
			if (!value)
				return (NULL);
			return (value);
		}
	}
	value = malloc(sizeof(char) * 1);
	if (!value)
		return (NULL);
	*value = '\0';
	return (value);
}

/**
 * @brief only replace the first variable in the string, 
 * because we run this in a loop
 * in the func expand_variables
 * first while loop: copy from old str to new str until you hit an $
 * second while loop: go through the value and copy that into the old str
 * 		now i is in the new str at the first sign after the repaced variable
 * 		f.e. "Hallo $USER und so" -> "Hallo maxrehberg und so" 
 * 			i is between the g and the u on the emptyspace
 * the rest of the Schützenfest is the len of the old str minus
 * 		the len of the variable plus the len of the value
 * 			because we replaced them, minus i (there we are right now)
 * last while loop: go till the end of the new string and
 * 		copy the rest to it. 
 * new_str[i] = old_str[i - num_value + num_var + 1]; 
 * 		There is a plus 1 at the end because we want to jump over the $ sign 
 * 		thats not included in num_var
 * set a \0 at the end
 * 
 * maybe a memory leak in:
 * 	ft_memcpy(&str[i[0]], &old_str[i[0] - num_value + num_var + 1], rest); 
 * 	rest copies the terminating \0 also
 * 
 */
char	*replace_first_var_in_str(char *str, char *value, \
	int num_var, int num_value)
{
	int		i[2];
	int		old_strlen;
	int		rest;
	char	*old_str;

	i[0] = -1;
	i[1] = -1;
	old_str = str;
	str = malloc(sizeof(char) * (ft_strlen(str) - num_var + num_value));
	if (!str)
		return (NULL);
	old_strlen = ft_strlen(old_str);
	while (old_str[++i[0]] != '$')
		str[i[0]] = old_str[i[0]];
	while (++i[1] < num_value)
		str[i[0]++] = value[i[1]];
	rest = old_strlen - num_var + num_value - i[0];
	i[1] = -1;
	ft_memcpy(&str[i[0]], &old_str[i[0] - num_value + num_var + 1], rest);
	free (old_str);
	return (str);
}
