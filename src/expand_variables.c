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
	int i;
	
	i = 1;
	while (!var_delimiter(str[i])) //can I do a while without a statement? 
		i++;
	return (i - 1);
}

char	*value_of_variable_from_env(char ***env, char *var, int len)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(var, env[i][0], len + 1))
		{
			//printf("str: %s  ptr: %p\n", env[i][1], env[i][1]);
			return (env[i][1]);
		}

	}
	return (NULL);
}

void	replace_first_var_in_str(char *new_str, char *old_str, char *value, int num_var, int num_value)
{
	int i;
	int j;
	int old_strlen = ft_strlen(old_str);

	i = -1;
	j = -1;
	while (old_str[++i] != '$') // plus copy
		new_str[i] = old_str[i];
	while (++j < num_value)
	{
		new_str[i++] = value[j];
	}
	int rest = old_strlen - (i - num_value + num_var);
	int k = -1;
	while (++k < rest) //vorher nullen, z.B. "Hallo $USER, wie" -> "Hallo maxrehberg, wie" 
	{
		new_str[i] = old_str[i - num_value + num_var + 1];
		i++;
	}
	new_str[i] = '\0';
}

/**
 * @brief Goes through a 2D char array (input_lexer) and looks for Variables in it with a $VARNAME
 * then looks for this name in info->env and replaces the $VARNAME with it's value 
 * what it found in the env
 * -> second while loop goes through the letters of the array. If it hits a $ sign, 
 * it's then processing the variable as follows:
 * 		how long is the variable name without the $ -> $USER -> 4 ; $VAR -> 3
 * 		copy the variabe name (var) (malloc) -> "$USER" -> "USER" 
 * 		let a char ptr point to the value of the variable in env (value) with var
 * 		; if value == NULL -> set num_value to 0, else count the chars of the value (num_value)
 * 		count the initial (strlen) (array[i])
 * 		malloc space for the new string 
 * 				(old string len (strlen) - variable len (num_var + 1) - value len (num_value) + 1)
 * 				num_var + 1 because of the $ sign thats not in num_var included and + 1 at the end for the \0
 * 		replace the first variable in the string: "hallo $USER und $HOME" -> "hallo maxrehberg und $HOME"
 * 		free var and the old string (buf)
 * 	only do all the things above when it's not in single quotes 'Hallo $USER' -> 'Hallo $USER'
 * 																"Hallo $USER" -> "Hallo maxrehberg"
 */
int	expand_variables(char	**array, char ***env, t_info *info)
{
	int i;
	int j;
	int s_quote;
	char *buf;
	char *old_str;
	char *var;
	char *value;
	int	num_var;
	int	num_value;
	int strlen;

	i = -1;
	s_quote = 0;
	while (array[++i])
	{
		j = -1;
		old_str = array[i];
		while (array[i][++j])
		{
			buf = &array[i][j];
			if (!s_quote && *buf == '$')
			{
				num_var = variable_name_count(buf);
				var = ft_substr(buf, 1, num_var);
				if (!var)
					return (!error(ERR_MALLOC_EXPAND_VARIABLES, info));
				value = value_of_variable_from_env(env, var, num_var);
				if (!value)
					num_value = 0;
				else
					num_value = ft_strlen(value);
				strlen = ft_strlen(array[i]);
				array[i] = malloc(sizeof(char) * (strlen - (num_var + 1) + num_value + 1));
				replace_first_var_in_str(array[i], old_str, value, num_var, num_value);
				free (var);
				free (buf);
			}
			if (*buf == '\'')
				s_quote = !s_quote;



			// buf = &array[i][j];
			// old_str = array[i];
			// if (!s_quote && *buf == '$')
			// {
			// 	num_var = variable_name_count(buf);
            //     // printf("num_var: %d\n", num_var);
            //     var = ft_substr( buf, 1, num_var); // malloc and copy var name
            //     //save malloc from substr
            //     // printf("_%s_\n", var);
            //     value = value_of_variable_from_env(env, var, num_var);
			// 	if (!value)
			// 	{
			// 		num_value = 0;
			// 	}
			// 	else
            //     	num_value = ft_strlen(value);
            //     // lexer: "$vari ist gut" -> "hallo ist gut" -> needs more memory
            //     int strlen = ft_strlen(array[i]); //------------------------------------ // what if empty string?
            //     array[i] = malloc(sizeof(char) * (strlen - (num_var + 1) + num_value + 1));
            //     // always starts with a $ ?? "hallo $vari du da" ??
            //     replace_first_var_in_str(array[i], old_str, value, num_var, num_value);
			// 	// printf("old: %s\n", old_str);
			// 	// printf("new: %s\n", array[i]); //newline irgendwo her

            //     // copy old text   whats with "hallo $vari und so $vari lala"

			// }

			// if (*buf == '\'')
			// {
			// 	s_quote = !s_quote;
			// }
		}
	}
}