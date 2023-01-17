#include "../inc/minishell.h"

int	sep(char c)
{
	if(c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	red(char c)
{
	if(c == '<' || c == '>')
		return (1);
	return (0);
}

/**
 * @brief returns ptr to place after the redirect signs
 * saves num of signs in buf if buf is not NULL
 */
char	*after_red(char *str, int *buf)
{
	int i = 0;
	while(red(*str) && *str != '\0')
	{
		i++;
		str++;
	}
	if (buf)
		*buf = i;
	return (str);
}

char	*after_sep(char *str, int *buf)
{
	int i = 0;
	while(sep(*str) && *str != '\0')
	{
		i++;
		str++;
	}
	if (buf)
		*buf = i;
	return (str);
}    

char	*after_word(char *str, int *buf)
{
	int i = 0;
	while(!sep(*str) && !red(*str) && *str != '\0')
	{
		i++;
		str++;
	}
	if (buf)
		*buf = i;
	return (str);
}

int	count_parts(char *str)
{
	int i = 0;

	while(*str != '\0')
	{
		if(sep(*str))
		{
			i++;
			str = after_sep(str, NULL);
		}
		if(red(*str))
		{
			i++;
			str = after_red(str, NULL);
		}
		if(!sep(*str) && !red(*str))
		{
			i++;
			str = after_word(str, NULL);
		}
	}
	return (i);
}

char *mal_copy(char * str)
{
	int word_len = 0;
	char *word;
	int i = 0;

	after_word(str, &word_len);
	word = malloc(sizeof(char) * (word_len + 1));
	word[word_len] = '\0';
	while (i < word_len)
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}		

void	fill_array(char **array, char *str)
{
	int part_i = 0;
	int part_len = 0;
	int i;
	char *buf;

	while(*str)
	{
		if(sep(*str)) // evtl in a separate func
			buf = after_sep(str, &part_len);
		else if(red(*str))
			buf = after_red(str, &part_len);
		else if(!sep(*str) && !red(*str))
			buf = after_word(str, &part_len);
		array[part_i] = malloc(sizeof(char) * (part_len + 1));
		if (array[part_i] == NULL)
			error(ERR_MALLOC_SPLIT);
		array[part_i][part_len] = '\0';
		i = -1;
		while (++i < part_len)
			array[part_i][i] = str[i];
		str = buf;
		part_i++;
	}
}

char	**split_lexer(char *str)
{
	int	word_count = 0;
	char **array;

	//handle unequal number of quotes (single, double)

	if(str == NULL || *str == 0) // maybe return a double pointer with malloced space -> better to handle in clean_up?
		return NULL;
	word_count = count_parts(str);
	array = malloc((sizeof(char *) * (word_count + 1)));
	array[word_count] = 0;
	fill_array(array, str);
	return (array);
}
