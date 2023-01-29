
#include "../inc/minishell.h"

/** compare echo with 5 characters (include \0), otherwise
 * it would be ok when you type echom (4 chars compares only up to o in echo)
 **/
void	cmd_identifier(char **cmd, t_info *info)
{
	if (!strncmp(cmd[0], "echo", 5))
		ft_echo(cmd);
	else if (!strncmp(cmd[0], "exit", 5))
		ft_exit(cmd);
	else if (is_an_executable(cmd[0], info))
		printf("cmd[0] is root_cmd = %s\n", info->root_cmd);
}

/**
 *  @brief the parser goes through the strings of the lexer one by one and 
 * the temporary struct t_parse_lexer is used. It holds the actual group we are in,
 * the category cat of the categoriser, the falg if the string belongs to a redirect.
 * 
 * @param info 
 */
void	parser(t_info *info) // after lexer.. groups and make space for ptr to group structs and group structs and clean_up
{
	t_parse_lexer a;
	t_parse_lexer *pl;

	pl = &a;
	pl->act_group = 0;
	int i;
	i = -1;

	add_history(info->prompt);

	info->input_lexer = ft_split_lexer(info->prompt);
	info->num_groups = count_groups(info);
	info->groups = init_groups(info);
	while (++i < info->num_groups)
		info->groups[i].arguments = ft_array_args(info->prompt);	// double pointer for array of arguments
	i = -1;
	while (info->input_lexer[++i]) // Null at end of group
	{

		if (!ft_strncmp(info->input_lexer[i], "|", 2))
			pl->act_group++;
		pl->cat = categorize(info->input_lexer[i]);

		pl->is_red = found_save_redirect(pl, info, info->input_lexer[i]);
	
		pl->is_exe = found_save_executable(pl, info, info->input_lexer[i], i); // cannot identify several executables in one group
		found_save_arguments(pl, info, i);
		printf("_%s_\n", info->input_lexer[i]);
		printf("redirect %d\n", pl->is_red);
		printf("executable %d\n", pl->is_exe);		
	}
	print_groups(info->groups, info); // möglich <> ??
}
