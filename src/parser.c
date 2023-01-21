
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

void	parser(t_info *info)
{
	int i;
	i = -1;
	int cat;
	// //char **cmd;
	add_history(info->prompt);
	// //cmd = ft_split(prompt, ' '); // only delimiting by ‘ ‘, not by tabs for example

	// //input_error_check(cmd); // no function until now
	// //cmd_identifier(cmd, info);
	info->input_lexer = ft_split_lexer(info->prompt);
	
	while (info->input_lexer[++i])
	{
													// ft_order can also be split in subfunctions -> one for testing only correct redirections (< test) (>>hallo.txt) and another subfunc can test 
 		printf("%s__", info->input_lexer[i]);		// only for testing purposes
		cat = categorize(info->input_lexer[i]);
		if (cat == WORD)
			printf("%d_exe?--", is_an_executable(info->input_lexer[i], info));
		printf("%d\n", cat);						// only for testing purposes
	}


}
