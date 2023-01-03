/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:49:02 by nrenz             #+#    #+#             */
/*   Updated: 2023/01/03 21:49:41 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("test> ");
		if (*prompt)
		{
			add_history(prompt);
			rl_replace_line("added to the history!", 1);
			sleep(1);
			//printf("in the loop");
		}
		
	}
	return (0);
}
