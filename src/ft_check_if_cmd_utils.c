#include "../inc/minishell.h"

char *check_if_path_found(char *path_to_executable, t_info *t_info, \
char *slash_added, char *slash_not_added)
{
	if (path_to_executable)
	{
		t_info->nb_root_cmd++;
		free_slash(slash_added, slash_not_added);
		return (path_to_executable);
	}
	return (NULL);
}
