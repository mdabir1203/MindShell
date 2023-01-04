/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:18:42 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/04 23:10:58 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(char **cmd)
{
	int i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd[i])
	{
		if (!strncmp(cmd[i], "-n", 3))
		{
			i++;
			flag = 1;
		}
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i+1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag == 1)
		ft_putchar_fd('%', 1);
	ft_putchar_fd('\n', 1);
}