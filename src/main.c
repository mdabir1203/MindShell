
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

/** readline returns a NULL if ctrl + d is hit
 * ctrl + c ist the signal SIGINT; ends child process?
 * ctrl + \ is the signal SIGQUIT; ends the bash?
 **/
int	main(void)
{
	char	*prompt;
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (2);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (2);
	while (1)
	{
		if (!(prompt = readline("test> "))) // test ersetzen durch "benutzer@machine Ordner % "
			clean_up(CTRL_D_PRESSED);
		process_input(prompt);
	}
	return (0);
}

