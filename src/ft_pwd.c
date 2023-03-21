#include "../inc/minishell.h"

void	ft_pwd(t_group *group)
{
	char	*cwd;

	if (group->arguments[1])
	{
		perror("pwd : too many arguments");
		exit(EXIT_FAILURE);
	}
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("failed");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
}
