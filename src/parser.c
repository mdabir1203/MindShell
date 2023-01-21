
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
													// Ranja, I got another idea. Let ft_order only test if the redirections are valid (< test) (>>hallo.txt),
													// also valid redirection: (> -na) -> if we can't name a file like this... open() (later in the execution part) will return a -1 and we can throw an error then...
													// -> reason for "only test if the redirections are valid": we have to test if the first word, beside all redirections, is a command, like this
													// (<test echo >> out.txt Hallo du da) -> this works even if echo does not take the input from test it writes "Hallo du da" into the file out.txt
													// I thought for doing it smart and simple we could first check if the redirections are correct and then cut them out of the group
													// -> this (<test echo >> out.txt Hallo du da) will then be (echo Hallo du da) and voila, it's very easy to check now if there is a command at the first place in the group
													// p.s. before cutting out the redirections we have to save them in the group struct -> we can thing about that later
 		printf("%s__", info->input_lexer[i]);		// only for testing purposes
		cat = categorize(info->input_lexer[i]);

		// here comes ft_order(cat)

		if (cat == WORD)
			printf("%d_exe?--", is_an_executable(info->input_lexer[i], info));
		printf("%d\n", cat);						// only for testing purposes
	}


}
