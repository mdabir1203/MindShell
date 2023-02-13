#include "../inc/minishell.h"

// Delimiter for Variables
int	var_delimiter(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (0);
	return (1);
}

/**
 * @brief Looks how many chars the variable has 
 * First char is $, so jump that (i = 1)
 * @return returns num of chars of the variable + 1 
 * ($var -> returns 4)
 */
int	variable_name_count(char *str)
{
	int i;
	
	i = 1;
	while (!var_delimiter(str[i])) //can I do a while without a statement? 
		i++;
}

void	expand_variables(char	**array)
{
	int i;
	int j;
	int s_quote;
	char *buf;
	char *var;

	i = -1;
	s_quote = 0;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
		{
			buf = &array[i][j];
			if (!s_quote && *buf == '$')
			{
				variable_name_count(buf);
				//var = ft_substr(buf, 1, ) // malloc and copy var name
				// look for var name in env
				// count how many chars the value of the var has // and above save the nums that the var name has
				// lexer: "$vari ist gut" -> "hallo ist gut" -> needs more memory
				// look how many chars the old str has
				// malloc( old_string - var_nums + value_nums )
				// always starts with a $ ?? "hallo $vari du da" ??
				// copy old text   whats with "hallo $vari und so $vari lala"

			}

			if (*buf == '\'')
			{
				s_quote = !s_quote;
			}
		}
	}
}