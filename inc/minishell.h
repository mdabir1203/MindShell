#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

//*********************************************************//
//**                FLAGS                               **//

//**                COLORS                   **//

# define BLINK "\033[5m"
# define RESET "\e[0m"

//**                PARSER CATEGORIES                    **//

# define REDIR_INPUT 4
# define REDIR_OUTPUT 5
# define REDIR_OUTPUT_APPEND 6
# define REDIR_INPUT_APPEND 7
# define PIPE 8
# define WORD 9
# define FLAG 11
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
# define CMD_CLEAR 38
# define BUILTIN_END 40

//**                ERROR FLAGS                          **//

# define ERR_MALLOC_SPLIT 41
# define ERR_MALLOC_INIT_GROUPS 42
# define ERR_CMD_NOT_FOUND 43
# define ERR_MALLOC_ARRAY_ARGS 44
# define ERR_WRONG_AMOUNT_QUOTATION_MARKS 45
# define ERR_MALLOC_SPLIT_ONE 46
# define ERR_NO_EQUAL_IN_EXPORT_ARG 47
# define ERR_EQUAL_IN_UNSET_ARG 48
# define ERR_MALLOC_EXPAND_VARIABLES 49
# define ERR_CD_NO_DIRECTORY 50

//**                OTHER FLAGS                          **//

# define CTRL_D_PRESSED 60
# define CLEAN_UP_REST_BEFORE_EXIT 61
# define CLEAN_UP_FOR_NEW_PROMPT 62

//**				TEXT OUTPUT							**//

# define STR_PROG_NAME "minishell:"
# define ERROR "error\n"
# define STR_EXIT_MULTIPLE "Word exit is enough!\n"
# define STR_EXIT_SUCCESSFULL "Exit successfull!\n"
# define MALLOC_FAIL "While memory allocation\n"
# define PIPE_ERROR_1 "-bash: syntax error near unexpected token `|'\n"
# define PIPE_ERROR_2 "This input is not allowed!\n"
# define STR_WRITE_ERROR "Command not found\n"
# define REDIRECT_ERROR_1 "No such file or directory\n"
# define INVALID_IDENTIFIER "Not a valid identifier\n"
# define QUOTATION_MARKS "Wrong amount of quotation marks\n"
# define EQUAL_SIGN "No '=' sign in export argument\n"

//**				pipes							**//

# define WRITE 1
# define READ 0

//*********************************************************//
//**                STRUCTURES                          **//

/**
 * @brief  info struct holds all informations
 * @prompt:	stores the whole command line the user types in 
 * -> has to be freed in the main while loop before user can
 *  enter the next commands
 * @input_lexer: holds a 2d char array, all the commands, 
 * arguments, emptyspacec, pipes and so on are separated
 * @env: 3d array to all the environment variables.
 * *env is an array of ptrs for the different vars.
 * each of the ptrs point to an array of 2 ptrs. 
 * [0] points to the string of the env variables name.
 * [1] points to the string of the variables value.
 * @paths: 2d char array that holds all the paths to the bin folders
 * that are saved in the env variable PATH
 * @root_cmd: ask Nick
 * @nb_root_cmd: ask Nick
 * @num_groups: number of groups in the prompt (separated by pipes | )
 * @groups: ptr to all the groups. All groups are behind each other
 * in the memory.
 * There are no pointers in between that point to every group. 
 * The last group is 0. Cannot check in while loop
 * like this while(group[i]) -> has to be done like this
 * while(++i < info->num_groups) don't know why.
 */
typedef struct s_info
{
	char			*prompt;
	char			**input_lexer;
	char			***env;
	char 			**envp;
	char			**paths;
	int				nb_root_cmd;
	int				num_groups;
	struct s_group	*groups;
}					t_info;

/*
The code is designed to parse commands typed into the minishell,
assuming that each command is separated by a pipe symbol (|).
The parsed commands are stored in groups, where each group contains
information about the command, its arguments, 
and any input/output redirection or piping.
The first argument in each group is always the command itself. 
The code also handles built-in commands and executable commands
with their respective 
paths.
The parsed information is then used in the executer.
*/
typedef struct s_group
{
	int				exit_status;
	char			**arguments;
	char			*path;
	int				builtin;
	int				redir_in;
	char			*redir_infile;
	int				redir_out;
	char			*redir_outfile;
	int				pipe_in;
	int				pipe_out;
	int				pipe_fd[2];
	pid_t			pid;
	t_info			*info;
}					t_group;

/**
 * @brief temp struct for the while loop in the parser
 * 
 * @cat: 		 the int value the categorizer returns f.e. (REDIRECT_OUTPUT)
 * @act_group:	actual group of commands f.e. (echo Hallo | cat) before the 
 *              | it's 0 after it's 1
 * @is_red:		is redirect -> the int value that found_save_redirect()
 *              returns -> 1 for yes, 0 no redirect
 * @is_exe:		is executable -> int value that found_save_executable() 
 *              returns -> 1 for yes, 0 no exe
 */
typedef struct s_parse_lexer
{
	int				cat;
	int				act_group;
	int				is_red;
	int				is_exe;

}					t_parse_lexer;

//*********************************************************//
//**                FUNCTIONS                           **//
//*******************************************************//

//**** prompt.c ****//

void				change_promptcolor(void);

//**** categorize.c ****//

int					categorize(char *str);

//**** check_if_cmd.c ****//
void				free_slash(char *slash_added, char *slash_not_added);
int					check_if_access_in_parser(char *cmd, t_info *t_info,
						char **path_to_executable);

char				*is_an_executable(char *cmd, t_info *t_info);

//**** check_if_cmd_utils.c****//
char				*check_if_path_found(char *path_to_executable,
						t_info *t_info, char *slash_added,
						char *slash_not_added);

//**** input_check.c ****//

int					parser_error_check(t_info *info, t_parse_lexer *pl, int i);
int					executer_error_check(t_info *info, t_group *groups);

//**** clean_up_utils.c ****//

void				clean_up_group_structs(t_info *info);
void				clean_up_info_struct(t_info *info);
void				clean_up_paths(t_info *info);
void				clean_up_prompt(t_info *info);
void				clean_up_env(t_info *info);

//**** clean_up.c ****//

void				clean_up_lexer(t_info *info);
void				clean_up(int clean_up_code, t_info *info);

//**** ft_message.c ****//

int					input_message(char *str, int exit_no);

//**** error.c ****//

int					error(int err, t_info *info);

//**** executer.c ****//

void				executer(t_group *group);

//**** expand_variables_utils.c ****//

int					var_delimiter(char c);
int					variable_name_count(char *str);
char				*exit_status(void);
char				*value_of_variable_from_env(char ***env, char *var,
						int len);
char				*replace_first_var_in_str(char *str, char *value,
						int num_var, int num_value);

//**** expand_variables.c ****//

char				*value_of_variable_from_env(char ***env, char *var,
						int len);
int					expand_variables(char **array, t_info *info);

//**** ft_pwd.c ***//

void				ft_pwd(t_group *group);

//**** ft_cd.c ****//

void				ft_cd(char **args, t_info *info);

//**** ft_echo.c ****//

void				ft_echo_helper(char **args, int arg_j);
void				ft_echo(char **args, int pipe_out);

//**** ft_exit.c ****//

void				ft_exit(t_info *info);

//**** ft_env.c ****//
void				ft_env(t_info *info);

//**** ft_clear.c ****//
void				ft_clear(void);

//**** ft_export_sub_sub.c ****//

void				populate_var(char *str, char *arg);
void				populate_cont(char *str, char *arg);
void				export_with_no_args(t_info *info);
int					var_pos_in_env_export(char *arg, char ***env);
void				replace_cont_of_var(char *arg, char ***env, t_info *info);

//**** ft_export_sub.c ****//

int					num_args(char **args);
int					num_env_args(char ***args);
void				populate_new_env_with_old_args(char ***new_env,
						char ***old_env);
int					num_var_chars(char *str);
int					num_cont_chars(char *str);

//**** ft_export.c ****//

int					num_env_args(char ***args);
int					ft_export(char **args, t_info *info);

//**** ft_split_lexer_utils_2.c ****//

char				*after_sep(char *str, int *buf);
char				*after_pipe(char *str, int *buf);
char				*after_quote(char *str, int *buf);
char				*after_word(char *str, int *buf);
int					count_parts(char *str);

//**** ft_split_lexer_utils.c ****//

int					sep(char c);
int					red(char c);
int					quote(char c);
int					pipesign(char c);
char				*after_red(char *str, int *buf);

//**** ft_split_lexer.c ****//

int					sep(char c);
int					count_parts(char *str);
char				**ft_split_lexer(char *str, t_info *info);

//**** ft_unset.c ****//

int					ft_unset(char **args, t_info *info);

//**** init.c ****//

t_info				*init(char **envp);
char				**ft_array_args(char *str, t_info *info);
t_group				*init_groups(t_info *info);

//**** make_env_arr.c ****//

void				make_env(char **envp, t_info *info);

//**** parser_utils_3.c ****//

int					count_groups(t_info *info);
void				shift_str_left(char *str);
void				delete_quotationmarks_one_string(char *str);
void				delete_quotationmarks(char **array);

//**** parser_utils_2.c ****//

int					is_redirect(int num);
int					found_save_redirect_sub(int *before_cat, t_info *info,
						char *act_lexer, t_parse_lexer *pl);
int					found_save_redirect(t_parse_lexer *pl, t_info *info,
						char *act_input_lexer_str, int i);
int					is_builtin(char *str);

//**** parser_utils.c ****//

int					found_save_redirect(t_parse_lexer *pl, t_info *info,
						char *act_input_lexer_str, int i);
int					found_save_executable(t_parse_lexer *pl, t_info *info,
						char *act_input_lexer_str, int i);
void				found_save_arguments(t_parse_lexer *pl, t_info *info,
						int i);
void				pipe_detector(t_parse_lexer *pl, t_info *info);
int					count_groups(t_info *info);
void				delete_quotationmarks(char **array);

//**** parser.c ****//

int					parser_loop(t_info *info, t_parse_lexer *pl, int i);
int					parser(t_info *info);

//**** redirect_and_pipe_helpers.c ****//

int					redir_in(t_group *group);
void				redir_out(t_group *group);
void				make_pipe(t_group *group);
void				replace_pipe_in_next_group(t_group *group, int new_pipe_in);
int					next_have_pipe_out(t_group *group);

//**** helpers_fds_builtin.c ****//

void				dup_fd(int fd_new, int fd_old, t_info *info);
void				closing_fds(t_group *group);
int					check_access_infile_outfile(t_group *group);
void				builtins_with_output(t_group *group);
void				builtin_no_piping(t_group *group);

//**** heredoc.c ****//
int					heredoc_sub(t_group *group, char *str[3], int fd[2]);
int					heredoc(t_group *group);

//**** helpers_fds.c ****//
int					check_access_infile_outfile(t_group *group);
void				dup_fd(int fd_new, int fd_old, t_info *info);
void				closing_fds(t_group *group);
void				handle_redir_and_dup(t_group *group);

//**** ft_wait_and_exit.c ****//
void				wait_and_exit_status(t_group *tmp);

//**** tests.c ****//

void				p2d(char **ptr);
void				print_groups(t_group *groups, t_info *info);

void				remove_ctrl_c_feed(void);

extern int			g_exit_status;

#endif
