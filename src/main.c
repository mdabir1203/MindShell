/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:49:02 by nrenz             #+#    #+#             */
/*   Updated: 2023/01/04 19:45:46 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**	SIGQUIT should do nothing
 * 
 **/
void	signal_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
		printf("OUCH, did you hit Ctrl-C?\n");
	(void) *context;
	(void) *info;
	exit(0);
}

/** readline returns a NULL if ctrl + d is hit
 * ctrl + c ist the signal SIGINT
 * ctrl + \ is the signal SIGQUIT
 **/
int	main(void)
{
	char	*prompt;
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (2);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (2);
	while (1)
	{
		if (!(prompt = readline("test> "))) // test ersetzen durch "benutzer@machine Ordner % "
			clean_up(CTRL_D_PRESSED);
		process_input(prompt);
	}
	return (0);
}

