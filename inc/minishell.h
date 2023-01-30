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

//**                PARSER CATEGORIES                    **//

# define REDIR_INPUT 4
# define REDIR_OUTPUT 5
# define REDIR_OUTPUT_APPEND 6
# define REDIR_INPUT_APPEND 7
# define PIPE 8
# define WORD 9
# define FLAG 11 // we don't need to cat it if the ft_order says ok to that ( > -n) then we need to check that again, when using open() it will return a -1 I think if it's not a valid file name.
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

# define ERR_MALLOC_SPLIT 41
# define ERR_MALLOC_INIT_GROUPS 42

//**                OTHER FLAGS                          **//

# define CTRL_D_PRESSED 43
# define CLEAN_UP_REST_BEFORE_EXIT 44
# define CLEAN_UP_FOR_NEW_PROMPT 45

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
	char			*prompt;
	char			**input_lexer;
	char			***env;
	char			**paths;
	char			*root_cmd;
	int				nb_root_cmd;
	int				num_groups;
	struct s_group	*groups;
}	t_info;

typedef struct s_group
{
	char	**arguments;
	char	*cmd;
	char	*path;
	int		redirect_input;
	char 	*redirect_input_filename;
	int		redirect_output;
	char 	*redirect_output_filename;
	int		pipe_in;
	int		pipe_out;
}	t_group;

/**
 * @brief temp struct for the shile loop in the parser
 * 
 * @cat 	the int value the categorizer returns f.e. (REDIRECT_OUTPUT)
 * @act_group 	actual group of commands f.e. (echo Hallo | cat) before the | it's 0 after it's 1
 * @is_red		is redirect -> the int value that found_save_redirect() returns -> 1 for yes, 0 no redirect
 * @is_exe		is executable -> int value that found_save_executable() returns -> 1 for yes, 0 no exe
 */
typedef struct s_parse_lexer
{
	int		cat;
	int		act_group;
	int		is_red;
	int		is_exe;

}	t_parse_lexer;


//*********************************************************//
//**                FUNCTIONS                           **//
//*******************************************************//

//**** categorize.c ****//

int categorize(char *str);

//**** input_check.c ****//

void	input_error_check(char **cmd);

//**** clean_up.c ****//

void	clean_up_group_structs(t_info *info);
void	clean_up_prompt(t_info *info);
void	clean_up_lexer(t_info *info);
void	clean_up(int clean_up_code, t_info *info);

//**** ft_message.c ****//

int input_message(char *str, int exit_no);

//**** error.c ****//

int	error(int err, t_info *info);


//**** ft_echo.c ****//

void	ft_echo(char **cmd);

//**** ft_exit.c ****//

void	ft_exit(char **cmd);

//**** ft_split_lexer.c ****//

int	count_parts(char *str);
char	**ft_split_lexer(char *str);

//**** init.c ****//

t_info	*init(char **envp);
t_group *init_groups(t_info *info);


//**** make_env_arr.c ****//

void	make_env(char **envp, t_info *info);

//**** parser_utils.c ****//

int		found_save_redirect(t_parse_lexer *pl, t_info *info, char *act_input_lexer_str);
int		found_save_executable(t_parse_lexer *pl, t_info *info, char *act_input_lexer_str, int i);
char	**ft_array_args(char *str);
void	found_save_arguments(t_parse_lexer *pl, t_info *info, int i);
void	pipe_detector(t_parse_lexer *pl, t_info *info);
int		count_groups(t_info *info);

//**** parser.c ****//

void	parser(t_info *info);

void	test_env_vars(t_info *info);

int	is_an_executable(char *prompt, t_info *info);

//**** tests.c ****//

void	p2d(char **ptr);
void	print_groups(t_group *groups, t_info *info);


#endif
