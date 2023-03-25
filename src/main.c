#include "../inc/minishell.h"

/* It removes the visual feedback
 * after signal gets handled
 * -> ICANON flag when removed input
 * is processed immediately as each
 * char is typed.
 * &= ~: bitwise negation -> to disable attributes
 * ECHOCTL: Control chars are not displayed
 * TCSANOW: change term attrib in midsession
 *          wout waiting for next read/write 
 */
void	remove_ctrl_c_feed(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/*
 * SIGQUIT should do nothing
 */
void	signal_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	remove_ctrl_c_feed();
	(void)context;
	(void)*info;
}

int	ft_signal(struct sigaction sa)
{
	sa = (struct sigaction){.sa_sigaction = signal_handler};
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (2);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (2);
	return (0);
}

/** readline returns a NULL if ctrl + d is hit
 * ctrl + c ist the signal SIGINT
 * ctrl + \ is the signal SIGQUIT
 SA_SIGINFO: The signal handler takes three arguments, not one.  In
              this case, sa_sigaction should be set instead of
              sa_handler.  This flag is meaningful only when
              establishing a signal handler.
**envp environment for env.
 **/
int		g_exit_status = 0;

int	main_loop(t_info *info)
{
	change_promptcolor();
	printf("%s", RESET);
	info->prompt = readline("minishelly> ");
	if (info->prompt == NULL)
	{
		write(1, "\n", 1);
		clean_up(CTRL_D_PRESSED, info);
	}
	if (!parser(info) || !ft_strncmp(info->prompt, "minishell\0", 10)
		|| !ft_strncmp(info->prompt, ".\0", 2) || !ft_strncmp(info->prompt,
			"..\0", 3))
	{
		clean_up(CLEAN_UP_FOR_NEW_PROMPT, info);
		return (1);
	}
	executer(info->groups);
	clean_up(CLEAN_UP_FOR_NEW_PROMPT, info);
	//printf("%s%s", BLINK, RESET);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	t_info				*info;

	ft_memset(&sa, 0, sizeof(sa));
	if (argc > 1 || argv[1])
		return (1);
	ft_signal(sa);
	info = init(envp);
	if (!info)
		return (1);
	if (info->prompt)
		printf("prompt");
	printf("Welcome to the minishell!\n");
	while (1)
	{
		main_loop(info);
	}
	clean_up(CLEAN_UP_REST_BEFORE_EXIT, info);
	return (0);
}
