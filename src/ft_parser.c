#include "../inc/minishell.h"

/** To color the prompt **/

void	change_promptcolor(void)
{
	int	index;
	const char *colors[] = {"\033[31m", "\033[32m", "\033[33m", //
							"\033[34m", "\033[35m", "\033[36m", "\033[37m"};
	index = rand() % 7;
	printf("%s", colors[index]);

}

/*
* function to shorten parser function to < 25 lines.
*/
int	parser_loop(t_info *info, t_parse_lexer *pl, int i)
{
	if (!ft_strncmp(info->input_lexer[0], "exit", 5))
		ft_exit(info);
	if (!ft_strncmp(info->input_lexer[i], "|", 2))
	{
		if (ft_strncmp(info->input_lexer[0], "|", 2)
			|| (ft_strncmp(info->input_lexer[0], " ", 1)
				&& ft_strncmp(info->input_lexer[1], "|", 2)))
			pl->act_group++;
	}
	pl->cat = categorize(info->input_lexer[i]);
	pl->is_red = found_save_redirect(pl, info, info->input_lexer[i], i);
	pl->is_exe = found_save_executable(pl, info, info->input_lexer[i], i);
	if (!parser_error_check(info, pl, i))
		return (0);
	found_save_arguments(pl, info, i);
	pipe_detector(pl, info);
	return (1);
}

/**
 *  @brief parser goes through the strings of lexer one by one and 
 * the temporary struct t_parse_lexer is used. It holds the actual group
 * we are in, the category cat of the categoriser, the flag if 
 * the string belongs to a redirect.
 * 
 * @param info 
 */
int	parser(t_info *info)
{
	t_parse_lexer	a;
	t_parse_lexer	*pl;
	int				i;

	pl = &a;
	pl->act_group = 0;
	i = -1;
	add_history(info->prompt);
	info->input_lexer = ft_split_lexer(info->prompt, info);
	if (!info->input_lexer)
		return (0);
	if (!expand_variables(info->input_lexer, info))
		return (0);
	info->num_groups = count_groups(info);
	info->groups = init_groups(info);
	while (++i < info->num_groups)
		info->groups[i].arguments = ft_array_args(info->prompt, info);
	i = -1;
	while (info->input_lexer[++i])
	{
		if (!parser_loop(info, pl, i))
			return (0);
	}
	delete_quotationmarks(info->input_lexer);
	return (1);
}
