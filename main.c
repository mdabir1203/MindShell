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

int	main(void)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("test> ");
		if (*prompt)
		{
			add_history(prompt);
			printf("in the loop");
		}
	}
	return (0);
}
