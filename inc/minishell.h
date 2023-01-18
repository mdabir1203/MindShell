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

//**                PARSER CATEGORIES                    **//

# define REDIR_INPUT 4
# define REDIR_INPUT_PLUS 7
# define REDIR_OUTPUT 5
# define REDIR_OUTPUT_APPEND 6
# define PIPE 8
# define WORD 9
# define FLAG 11
# define BUILTIN_CMD 10

//**                ERROR FLAGS                          **//

# define ERR_MALLOC_SPLIT 2

//**                MODES OF EXECUTION                   **//

# define MODE_INPUT 1
# define MODE_INPUT_PLUS 2
# define MODE_OUTPUT 4
# define MODE_OUTPUT_APPEND 8
# define MODE_AND 16
# define MODE_PIPE_IN 32
# define MODE_PIPE_OUT 64

//*********************************************************//
//**                STRUCTURES                          **//

typedef struct s_info
{
	char	*prompt;
	char	***env;
	char **paths;
	char *root_cmd;
	int	nb_root_cmd;
}	t_info;


//*********************************************************//
//**                FUNCTIONS                           **//
//*******************************************************//

//*********************************************************//
//**                FUNCTIONS                           **//
//*******************************************************//


//**** clean_up.c ****//

void	clean_up(int clean_up_code);


//**** error.c ****//

int	error(int err);


//**** ft_echo.c ****//

void	ft_echo(char **cmd);


//**** init.c ****//

t_info	*init(char **envp);


//**** make_env_arr.c ****//

void	make_env(char **envp, t_info *info);


//**** process_input.c ****//

void	process_input(char *prompt, t_info *info);

void	test_env_vars(t_info *info);

int	is_an_executable(char *prompt, t_info *info);


#endif
