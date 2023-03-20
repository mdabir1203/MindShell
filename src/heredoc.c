#include "../inc/minishell.h"

/**
 * @brief //temp str[0] , buf str[1]
 * 
 * @param group 
 * @param str 
 * @param fd 
 * @return int 
 */
int	heredoc_sub(t_group *group, char *str[3], int fd[2])
{
	while (!str[0][0] || ft_strncmp(str[0], group->redir_infile, \
		ft_strlen(group->redir_infile) + 1))
	{
		free (str[0]);
		str[0] = readline("> ");
		if (!str[0])
			break ;
		str[2] = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(str[2]);
		str[2] = str[1];
		str[1] = ft_strjoin(str[1], "\n");
		free (str[2]);
	}
	if (!str[0])
		write(fd[1], str[1], ft_strlen(str[1]));
	else
		write(fd[1], str[1], ft_strlen(str[1]) - \
			ft_strlen(group->redir_infile) - 1);
	close(fd[1]);
	return (fd[0]);
}

/**
 * @brief while readline not EOF
 * join from readline
 * 
 * @return int 
 */
int	heredoc(t_group *group)
{
	int		fd[2];
	char	*str[3];

	str[0] = malloc(1);
	str[0][0] = 0;
	str[1] = malloc(1);
	str[1][0] = 0;
	if (!group->redir_infile)
	{
		perror("syntax error near unexpected token");
		g_exit_status = 1;
		free (str[0]);
		free (str[1]);
		exit(1);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe fail");
		return (-1);
	}
	fd[0] = heredoc_sub(group, str, fd);
	return (fd[0]);
}
