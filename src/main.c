
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
int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	struct sigaction	sa;
	t_info	*info;

	if (argc > 1 || argv[1])
		return (1);
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (2);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (2);
	info = init(envp);
	if(info->prompt)
		printf("prompt"); //to silence the warning
	printf("Welcome to the minishell!\n");
	//test_env_vars(info); //uncomment if you want to see the env and path arrays in info
	while (1)
	{
		if (!(prompt = readline("test> "))) // test ersetzen durch "benutzer@machine Ordner % "
			clean_up(CTRL_D_PRESSED);
		process_input(prompt, info);
	}
	return (0);
}

