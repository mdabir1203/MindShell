/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:49:02 by nrenz             #+#    #+#             */
/*   Updated: 2023/01/03 16:59:32 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
		printf("OUCH, did you hit Ctrl-C?\n");
	if (sig == SIGQUIT)
		printf("OUCH, did you quit\n");
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
		prompt = readline("test> ");
		if (prompt == NULL)
		{
			printf("is NULL\n");
			exit(0);
		}
		if (*prompt)
		{
			add_history(prompt);
			printf("%s\n", prompt);
			//rl_replace_line("added to the history!", 1);
			sleep(1);
		}
	}
	return (0);
}

