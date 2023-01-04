/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:41:25 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/04 19:43:38 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cmd_identifier(char **cmd)
{
	if (!strncmp(cmd[0], "echo", 4)) // "echom klsdjfk" klappt auch
		ft_echo(cmd);
}

void	process_input(char *prompt)
{
	char **cmd;
	add_history(prompt);
	cmd = ft_split(prompt, ' ');

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