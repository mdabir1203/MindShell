
#include "../inc/minishell.h"

/**
 *  @brief the parser goes through the strings of the lexer one by one and 
 * the temporary struct t_parse_lexer is used. It holds the actual group we are in,
 * the category cat of the categoriser, the falg if the string belongs to a redirect.
 * 
 * @param info 
 */
int	parser(t_info *info) // after lexer.. groups and make space for ptr to group structs and group structs and clean_up
{
	t_parse_lexer a;
	t_parse_lexer *pl;

	pl = &a;
	pl->act_group = 0;
	int i;
	i = -1;

	add_history(info->prompt);
	info->input_lexer = ft_split_lexer(info->prompt, info);
	if (!info->input_lexer)
		return (0);
	// expand_variables(info->input_lexer, info->env, info);
	if (!expand_variables(info->input_lexer, info))
		return (0);
	delete_quotationmarks(info->input_lexer);
	info->num_groups = count_groups(info);
	info->groups = init_groups(info);
	while (++i < info->num_groups)
		info->groups[i].arguments = ft_array_args(info->prompt, info);
	i = -1;
	while (info->input_lexer[++i]) //if we also want to handle " | echo hallo" then pl->act_group < info->num_groups
	{
		if (!ft_strncmp(info->input_lexer[0], "exit", 5))
			ft_exit(info);
		if (!ft_strncmp(info->input_lexer[i], "|", 2))
		{
			if (ft_strncmp(info->input_lexer[0], "|", 2) || (ft_strncmp(info->input_lexer[0], " ", 1) && ft_strncmp(info->input_lexer[1], "|", 2)))
				pl->act_group++;
		}

		pl->cat = categorize(info->input_lexer[i]);

		pl-> is_red = found_save_redirect(pl, info, info->input_lexer[i], i);
	
		pl->is_exe = found_save_executable(pl, info, info->input_lexer[i], i);

		if (!parser_error_check(info, pl, i))
			return (0);
		found_save_arguments(pl, info, i);

		pipe_detector(pl, info);
	}
	// p2d(info->paths);
	
	// print_groups(info->groups, info); // möglich <> ??
	// ft_unset(info->groups[0].arguments, info);
	
	// ft_echo(info->groups[0].arguments, info->groups[0].pipe_out);
	// return (0);
	// test_env_vars(info);
	return (1);
}
