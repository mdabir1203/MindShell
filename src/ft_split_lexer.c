#include "../inc/minishell.h"

// 	if (sep(*str))
	// 		buf = after_sep(str, &part_len);
	// 	else if (red(*str))
	// 		buf = after_red(str, &part_len);
	// 	else if (quote(*str))
	// 		buf = after_quote(str, &part_len);
	// 	else if (pipesign(*str))
	// 		buf = after_pipe(str, &part_len);
	// 	else
	// 		buf = after_word(str, &part_len);
char	*fill_array_sub(char *buf, char *str, int *part_len)
{
	if (sep(*str))
		buf = after_sep(str, part_len);
	else if (red(*str))
		buf = after_red(str, part_len);
	else if (quote(*str))
		buf = after_quote(str, part_len);
	else if (pipesign(*str))
		buf = after_pipe(str, part_len);
	else
		buf = after_word(str, part_len);
	return (buf);
}

/**
 * @brief runs though string and saves the parts into array[i].
 * gets with the subfuncs after_.... the amount of characters
 * in the next part and saves the value in part_len. buf points 
 * to the char after the part. 
 * Mallocs memory with part_len + 1 and saves the ptr in array[]
 * puts at the end of the new memory a \0
 * copies the chars of the part into the new memory. Sets str to
 * the char after the part. 
 * 
 * @param array 
 * @param str 
 */
int	fill_array(char **array, char *str, t_info *info)
{
	int		part_i;
	int		part_len;
	int		i;
	char	*buf;

	part_i = 0;
	part_len = 0;
	while (*str)
	{
		buf = fill_array_sub(buf, str, &part_len);
		array[part_i] = malloc(sizeof(char) * (part_len + 1));
		if (array[part_i] == NULL)
			return (!error(ERR_MALLOC_SPLIT, info));
		array[part_i][part_len] = '\0';
		i = -1;
		while (++i < part_len)
			array[part_i][i] = str[i];
		str = buf;
		part_i++;
	}
	return (1);
}

/**
 * @brief counts amount of quotation marks ("" and '')
 * "skdhfjh skjdhf" -> return 1
 * "skdhfjh skjdhf -> return 0
 * "skdhfjh ' skjdhf" -> return 1 ' is inside " ", that's ok
 * @returns 1 if the amount is correct
 */
int	correct_amount_of_quot_marks(char *str)
{
	int	double_quote;
	int	single_quote;

	double_quote = 0;
	single_quote = 0;
	while (*str)
	{
		if (*str == '\"' && !single_quote)
			double_quote = !double_quote;
		else if (*str == '\'' && !double_quote)
			single_quote = !single_quote;
		str++;
	}
	if (double_quote == 0 && single_quote == 0)
		return (1);
	return (0);
}

char	**ft_split_lexer(char *str, t_info *info)
{
	int		word_count;
	char	**array;

	word_count = 0;
	if (str == NULL || *str == 0)
		return (NULL);
	if (!correct_amount_of_quot_marks(str))
	{
		error(ERR_WRONG_AMOUNT_QUOTATION_MARKS, info);
		return (NULL);
	}
	word_count = count_parts(str);
	array = malloc((sizeof(char *) * (word_count + 1)));
	if (!array)
	{
		error(ERR_MALLOC_SPLIT_ONE, info);
		return (NULL);
	}
	array[word_count] = 0;
	if (!fill_array(array, str, info))
		return (NULL);
	return (array);
}
