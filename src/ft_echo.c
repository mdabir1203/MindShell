/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:18:42 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/04 20:07:29 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(char **cmd)
{
	int i;

	i = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i+1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
}