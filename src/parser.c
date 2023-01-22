
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

int	is_redirect(int num)
{
	if (num == REDIR_INPUT_APPEND)
		return (1);
	if (num == REDIR_INPUT)
		return (1);
	if (num == REDIR_OUTPUT_APPEND)
		return (1);
	if (num == REDIR_OUTPUT)
		return (1);
	return (0);
}

int	found_save_redirect(int cat, t_info *info, char *act_input_lexer_str, int act_group)
{
	int ret;
	static int before_cat = 0;
	//static int before_before_cat;


	ret = 0;
	if (cat == REDIR_INPUT_APPEND || cat == REDIR_INPUT)
	{
		ret = 1;
		before_cat = cat;
		info->groups[act_group].redirect_input = cat;// save int in group -> need group count in info or ptr to act group better
	}
	if (cat == REDIR_OUTPUT_APPEND || cat == REDIR_OUTPUT)
	{
		ret = 1;
		before_cat = cat;
		info->groups[act_group].redirect_output = cat;
		// save int in group
	}
	if (cat == SEPARATOR && is_redirect(before_cat))
		ret = 1;
	if (is_redirect(before_cat))
	{
		if (cat == WORD || cat == FLAG || (cat > BUILTIN_START && cat < BUILTIN_END))
		{
			ret = 1;
			if (before_cat == REDIR_INPUT_APPEND || before_cat == REDIR_INPUT)
				info->groups[act_group].redirect_input_filename = act_input_lexer_str;
			if (before_cat == REDIR_OUTPUT_APPEND || before_cat == REDIR_OUTPUT)
				info->groups[act_group].redirect_output_filename = act_input_lexer_str;
			before_cat = 0;
			// ptr *redirect_input_filename or *redirect_output_filename in t_group
		}
	}
	
	
	return (ret);
}

int	count_groups(t_info *info)
{
	int num_groups;
	int run;

	num_groups = 1;
	run = -1;
	while (info->input_lexer[++run])
	{
		if (!ft_strncmp(info->input_lexer[run], "|", 2))
			num_groups++;
	}
	return (num_groups);
}

void	parser(t_info *info) // after lexer.. groups and make space for ptr to group structs and group structs and clean_up
{
	int i;
	i = -1;
	int cat;
	// //char **cmd;
	add_history(info->prompt);
	// //cmd = ft_split(prompt, ' '); // only delimiting by ‘ ‘, not by tabs for example

	// //input_error_check(cmd); // no function until now
	// //cmd_identifier(cmd, info);
	//if (info->prompt == NULL || *info->prompt == 0)
		// return new line and wait for new command
	info->input_lexer = ft_split_lexer(info->prompt);
	info->num_groups = count_groups(info);
	info->groups = init_groups(info);

	int act_group = 0;
	while (info->input_lexer[++i])
	{
		if (!ft_strncmp(info->input_lexer[i], "|", 2))
			act_group++;
													// Ranja, I got another idea. Let ft_order only test if the redirections are valid (< test) (>>hallo.txt),
													// also valid redirection: (> -na) -> if we can't name a file like this... open() (later in the execution part) will return a -1 and we can throw an error then...
													// -> reason for "only test if the redirections are valid": we have to test if the first word, beside all redirections, is a command, like this
													// (<test echo >> out.txt Hallo du da) -> this works even if echo does not take the input from test it writes "Hallo du da" into the file out.txt
													// I thought for doing it smart and simple we could first check if the redirections are correct and then cut them out of the group
													// -> this (<test echo >> out.txt Hallo du da) will then be (echo Hallo du da) and voila, it's very easy to check now if there is a command at the first place in the group
													// p.s. before cutting out the redirections we have to save them in the group struct -> we can thing about that later
 		printf("%s_ ", info->input_lexer[i]);		// only for testing purposes
		cat = categorize(info->input_lexer[i]);

		// here comes ft_order(cat)

		printf(" _red?:%d_ ", found_save_redirect(cat, info, info->input_lexer[i], act_group));

		if (cat == WORD)
			printf("_%d_exe?- ", is_an_executable(info->input_lexer[i], info));
		printf("%d\n", cat);						// only for testing purposes
		printf("red input filename %s\n", info->groups[act_group].redirect_input_filename); // only for testing purposes
		printf("red output filename %s\n", info->groups[act_group].redirect_output_filename);	// only for testing purposes
	}
	

}
