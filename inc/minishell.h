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
# define REDIR_OUTPUT 5
# define REDIR_OUTPUT_APPEND 6
# define REDIR_INPUT_APPEND 7
# define PIPE 8
# define WORD 9
# define FLAG 11 // we don't need to cat it if the ft_order says ok to that ( > -n) then we need to check that again? -> anyways we need to check if the filename is valid
# define SEPARATOR 12

# define SEPARATOR_ONE " " // this is not so nice
# define SEPARATOR_TWO "\t"
# define SEPARATOR_THREE "\n"

# define BUILTIN_START 30
# define CMD_ECHO 31
# define CMD_EXIT 32
# define CMD_CD 33
# define CMD_PWD 34
# define CMD_EXPORT 35
# define CMD_UNSET 36
# define CMD_ENV 37
# define BUILTIN_END 40

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

//**				TEXT OUTPUT							**//

# define STR_PROG_NAME "minishell:"
# define ERROR "error\n"
# define STR_LETTER_ERROR "Start command with a small letter!\n"
# define STR_EXIT_MULTIPLE "Word exit is enough!\n"
# define STR_EXIT_SUCCESSFULL "Exit successfull!\n"
# define MALLOC_FAIL "While memory allocation\n"

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

//**** categorize.c ****//

int categorize(char *str);

//**** input_check.c ****//

void	input_error_check(char **cmd);

//**** clean_up.c ****//

void	clean_up(int clean_up_code);

//**** ft_message.c ****//

int input_message(char *str, int exit_no);

//**** error.c ****//

int	error(int err);


//**** ft_echo.c ****//

void	ft_echo(char **cmd);

//**** ft_exit.c ****//

void	ft_exit(char **cmd);

//**** init.c ****//

t_info	*init(char **envp);


//**** make_env_arr.c ****//

void	make_env(char **envp, t_info *info);


//**** process_input.c ****//

void	process_input(char *prompt, t_info *info);

void	test_env_vars(t_info *info);

int	is_an_executable(char *prompt, t_info *info);


#endif
