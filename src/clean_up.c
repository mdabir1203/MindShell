#include "../inc/minishell.h"

void	clean_up_lexer(t_info *info)
{
	char	**lexer;
	int		i;

	i = -1;
	lexer = info->input_lexer;
	if (!lexer)
		return ;
	while (lexer[++i])
	{
		free(lexer[i]);
	}
	free(lexer);
	lexer = NULL;
	info->input_lexer = NULL;
}

void	clean_up_arguments(t_info *info)
{
	int		i;

	i = -1;
	if (!info->groups)
		return ;
	while (++i < info->num_groups)
	{
		free(info->groups[i].arguments);
		info->groups[i].arguments = NULL;
	}
	free(info->groups->arguments);
}

void	clean_up_path_to_executable(t_info *info)
{
	int	i;

	i = -1;
	if (!info->groups)
		return ;
	while (++i < info->num_groups)
	{
		if (info->groups[i].path)
		{
			free(info->groups[i].path);
			info->groups[i].path = NULL;
		}
	}
}

/**
 * @brief line 64: Clean up rest before exit
 * should we use rrl_clear_history here to free history? 
 * maybe we can check with valgrind? please correct me 
 * if i dont understand (nick)
 */
void	clean_up(int clean_up_code, t_info *info)
{
	if (clean_up_code == CTRL_D_PRESSED)
	{
		clean_up(CLEAN_UP_FOR_NEW_PROMPT, info);
		clean_up(CLEAN_UP_REST_BEFORE_EXIT, info);
		exit(0);
	}
	if (clean_up_code == ERR_MALLOC_INIT_GROUPS)
		clean_up_group_structs(info);
	if (clean_up_code == CLEAN_UP_REST_BEFORE_EXIT)
	{
		clear_history();
		clean_up_env(info);
		clean_up_paths(info);
		clean_up_info_struct(info);
	}
	if (clean_up_code == CLEAN_UP_FOR_NEW_PROMPT)
	{
		clean_up_lexer(info);
		clean_up_prompt(info);
		clean_up_arguments(info);
		clean_up_path_to_executable(info);
		clean_up_group_structs(info);
	}
	if (clean_up_code == ERR_WRONG_AMOUNT_QUOTATION_MARKS)
		clean_up_prompt(info);
}
