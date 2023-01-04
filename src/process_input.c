/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:41:25 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/04 23:17:59 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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