
#include "../inc/minishell.h"

/** compare echo with 5 characters (include \0), otherwise
 * it would be ok when you type echom (4 chars compares only up to o in echo)
 **/
void	cmd_identifier(char **cmd)
{
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
