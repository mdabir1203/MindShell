
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/stat.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

//*********************************************************//
//**                FLAGS                               **//

# define CTRL_D_PRESSED 1


# define ERR_MALLOC_SPLIT 2

//*********************************************************//
//**                STRUCTURES                          **//

typedef struct s_info
{
	char	*prompt;

}	t_info;


//*********************************************************//
//**                FUNCTIONS                           **//
//*******************************************************//

void	process_input(char *prompt);

void	ft_echo(char **cmd);


void	clean_up(int clean_up_code);


#endif
