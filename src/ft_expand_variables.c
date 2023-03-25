#include "../inc/minishell.h"

void	handle_quotes(char	*buf, int *d_quote, int *s_quote)
{
	if (*buf == '\'' && !*d_quote)
		*s_quote = !*s_quote;
	if (*buf == '\"' && !*s_quote)
		*d_quote = !*d_quote;
}

int	expand_variables_sub(char **array, int i, char *buf, t_info *info)
{
	int		num_var;
	int		num_value;
	char	*var;
	char	*value;

	num_var = variable_name_count(buf);
	var = ft_substr(buf, 1, num_var);
	if (!var)
		return (!error(ERR_MALLOC_EXPAND_VARIABLES, info));
	value = value_of_variable_from_env(info->env, var, num_var);
	if (!value)
		return (!error(ERR_MALLOC_EXPAND_VARIABLES, info));
	if (*value == '\0')
		num_value = 0;
	else
		num_value = ft_strlen(value);
	array[i] = replace_first_var_in_str(array[i], value, num_var, num_value);
	if (!array[i])
		return (!error(ERR_MALLOC_EXPAND_VARIABLES, info));
	free (var);
	free (value);
	return (1);
}

/**
 * @brief Goes through a 2D char array (input_lexer) and looks for Variables
 * in it with a $VARNAME then looks for this name in info->env and replaces the 
 * $VARNAME with it's value what it found in the env
 * -> second while loop goes through the letters of the array. 
 * If it hits a $ sign
 * it's then processing the variable as follows:
 * 		how long is the variable name without the $ -> $USER -> 4 ; $VAR -> 3
 * 		copy the variabe name (var) (malloc) -> "$USER" -> "USER" 
 * 		let a char ptr point to the value of the variable in env (value) with var
 * 		; if value == NULL -> set num_value to 0, else count the chars 
 * 			of the value (num_value)
 * 		count the initial (strlen) (array[i])
 * 		malloc space for the new string 
 * 				(old string len (strlen) - variable len (num_var + 1) 
 * 					- value len (num_value) + 1)
 * 				num_var + 1 because of the $ sign thats not in num_var included 
 * 					and + 1 at the end for the \0
 * 		replace the first variable in the string: "hallo $USER und $HOME" -> 
 * 			"hallo maxrehberg und $HOME"
 * 		free var and the old string (buf)
 * 	only do all the things above when it's not in single 
 * 		quotes	'Hallo $USER' -> 'Hallo $USER'
 * 				"Hallo $USER" -> "Hallo maxrehberg"
 * 
 * recomendet testing: echo $USER; echo "hallo $USER"; echo "in $HOME we go";
 * echo "and $USER is $HOME and $USER not"; echo "_$USER_" ; echo "_$USER-da" 
 */
int	expand_variables(char	**array, t_info *info)
{
	int	i;
	int	j;
	int	s_quote;
	int	d_quote;
	int	ret;

	i = -1;
	s_quote = 0;
	d_quote = 0;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
		{
			handle_quotes(&array[i][j], &d_quote, &s_quote);
			if (!s_quote && array[i][j] == '$')
			{
				ret = expand_variables_sub(array, i, &array[i][j], info);
				if (ret != 1)
					return (ret);
				j--;
			}
		}
	}
	return (1);
}
