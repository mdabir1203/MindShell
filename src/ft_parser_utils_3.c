#include "../inc/minishell.h"

int	count_groups(t_info *info)
{
	int	num_groups;
	int	run;

	num_groups = 1;
	run = -1;
	while (info->input_lexer[++run])
	{
		if (info->input_lexer[1] == NULL)
			return (1);
		if (!ft_strncmp(info->input_lexer[0], "|", 2) || \
			(!ft_strncmp(info->input_lexer[0], " ", 2) && \
			!ft_strncmp(info->input_lexer[1], "|", 2)))
			return (1);
		if (!ft_strncmp(info->input_lexer[run], "|", 2))
			num_groups++;
	}
	return (num_groups);
}

void	shift_str_left(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = str[i + 1];
}

void	delete_quotationmarks(char	**array)
{
	int	i;
	int	j;
	int	d_quote;
	int	s_quote;

	i = -1;
	d_quote = 0;
	s_quote = 0;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
		{
			if (!d_quote && array[i][j] == '\'')
			{
				shift_str_left(&array[i][j--]);
				s_quote = !s_quote;
			}
			else if (!s_quote && array[i][j] == '\"')
			{
				shift_str_left(&array[i][j--]);
				d_quote = !d_quote;
			}
		}
	}
}
