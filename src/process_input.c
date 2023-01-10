
#include "../inc/minishell.h"

/** compare echo with 5 characters (include \0), otherwise
 * it would be ok when you type echom (4 chars compares only up to o in echo)
 **/
void	cmd_identifier(char **cmd)
{
	//we need to count number of arguments ex "cd dir1 | cat -e " is 5 argument and 2 of them is commands/executables (Nick or Nadine can make function that checks if an argument is an executable) (Nick wrote it)
	if (!strncmp(cmd[0], "echo", 5))
		ft_echo(cmd);
}

void	process_input(char *prompt)
{
	char **cmd;
	add_history(prompt);
	rl_replace_line("", 0);
	cmd = ft_split(prompt, ' '); // only delimiting by ‘ ‘, not by tabs for example

	cmd_identifier(cmd);

	// printf("%s\n", cmd[0]);
	// printf("%s\n", cmd[1]);
	// printf("%s\n", cmd[2]);
	// printf("%s\n", cmd[1]);
	// printf("%s\n", cmd[1]);
	// printf("%s\n", cmd[1]);
	// printf("%s\n", cmd[1]);
	// printf("%s\n", cmd[1]);
}
