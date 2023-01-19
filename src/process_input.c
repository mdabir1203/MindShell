
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

void	process_input(char *prompt, t_info *info)
{
	char **cmd;
	add_history(prompt);
	rl_replace_line("", 0);
	cmd = ft_split(prompt, ' '); // only delimiting by ‘ ‘, not by tabs for example

	input_error_check(cmd);
	cmd_identifier(cmd, info);

	// printf("%s\n", cmd[0]);
	// printf("%s\n", cmd[1]);
	// printf("%s\n", cmd[2]);
	// printf("%s\n", cmd[1]);
	// printf("%s\n", cmd[1]);
	// printf("%s\n", cmd[1]);
	// printf("%s\n", cmd[1]);
	// printf("%s\n", cmd[1]);
}
