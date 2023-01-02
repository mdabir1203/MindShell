/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:53:58 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/02 20:14:59 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include "/usr/local/Cellar/readline/8.2.1/include/readline/readline.h" 
# include "/usr/local/Cellar/readline/8.2.1/include/readline/history.h"

int	main(void)
{
	char *prompt = "test";
	readline(prompt);

	return (0);
}