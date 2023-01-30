
#include "../inc/minishell.h"

/**	SIGQUIT should do nothing
 * 
 **/
void	signal_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
		printf("OUCH, did you hit Ctrl-C?\n");
	(void) context;
	(void) *info;
	exit(0);
}

int	ft_signal(struct sigaction	sa)
{
	sa = (struct sigaction){.sa_sigaction = signal_handler}; // new
	//sa.sa_sigaction = &signal_handler;  // let's leave it in for now;
	sa.sa_flags = SA_SIGINFO; // without 5 errors from 5 contexts;
	//sigemptyset(&sa.sa_mask); // without maybe an error, depending on other errors, let's leave this line in for now;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (2);							// why returning 2?
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
int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	t_info	*info;

	if (argc > 1 || argv[1])
		return (1);
	ft_signal(sa);
	info = init(envp);
	if(info->prompt)
		printf("prompt"); //to silence the warning
	printf("Welcome to the minishell!\n");
	//printf("line 5 = %s\n", envp[4]);
	//test_env_vars(info); //uncomment if you want to see the env and path arrays in info
	int i = -1;
	while (++i < 3)
	{
		if (!(info->prompt = readline("test> "))) // test ersetzen durch "benutzer@machine Ordner % "
			clean_up(CTRL_D_PRESSED, NULL); // ATTENTION, hand over info somehow !!!
		parser(info);
		
		
		clean_up(CLEAN_UP_FOR_NEW_PROMPT, info);

		//break;
	}
	clean_up(CLEAN_UP_REST_BEFORE_EXIT, info);
	return (0);
}
