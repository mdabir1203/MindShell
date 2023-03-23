#include "../inc/minishell.h"

void	f_s_exe_sub(t_parse_lexer *pl, t_info *info, \
	int *already_found_exe, char *act_input_lexer_str)
{
	char		*path_to_executable;

	pl->is_exe = 1;
	*already_found_exe = 1;
	path_to_executable = is_an_executable(act_input_lexer_str, info);
	if (is_builtin(act_input_lexer_str))
	{
		info->groups[pl->act_group].builtin = is_builtin(act_input_lexer_str);
		info->groups[pl->act_group].arguments[0] = act_input_lexer_str;
		free(path_to_executable);
		path_to_executable = NULL;
	}
	else if (path_to_executable)
	{
		info->groups[pl->act_group].path = path_to_executable;
		info->groups[pl->act_group].arguments[0] = act_input_lexer_str;
	}
}

int	found_save_executable(t_parse_lexer *pl, t_info *info, \
	char *act_input_lexer_str, int i)
{
	static int	already_found_exe = 0;

	if (pl->cat == PIPE || i == 0)
		already_found_exe = 0;
	if (already_found_exe == 0 && !pl->is_red && pl->cat != PIPE \
		&& pl->cat != SEPARATOR)
	{
		f_s_exe_sub(pl, info, &already_found_exe, act_input_lexer_str);
		return (pl->is_exe);
	}
	if (act_input_lexer_str == NULL)
		already_found_exe = 0;
	pl->is_exe = 0;
	return (pl->is_exe);
}

void	fs_args_sub(t_parse_lexer *pl, t_info *info, int *arg_j, int i)
{
	*arg_j += 1;
	info->groups[pl->act_group].arguments[*arg_j] = \
		info->input_lexer[i];
}

/**
 * @brief The arguments are only ptrs that point tho the right lexer strings
 */
void	found_save_arguments(t_parse_lexer *pl, t_info *info, int i)
{
	int	arg_j;
	int	temp;

	arg_j = -1;
	temp = pl->cat;
	if (pl->is_exe == 1)
	{
		i--;
		while (info->input_lexer[++i])
		{
			pl->cat = categorize(info->input_lexer[i]);
			pl->is_red = found_save_redirect(pl, info, info->input_lexer[i], i);
			if (pl->cat == SEPARATOR || pl->is_red)
				continue ;
			else if (pl->cat == PIPE)
			{
				info->groups[pl->act_group].arguments[arg_j + 1] = NULL;
				break ;
			}
			else
				fs_args_sub(pl, info, &arg_j, i);
		}
		info->groups[pl->act_group].arguments[arg_j + 1] = NULL;
		pl->cat = temp;
	}
}

void	pipe_detector(t_parse_lexer *pl, t_info *info)
{
	//info->groups->pipe_in = 0;		init in init file!!!
	//info->groups->pipe_out = 0;
	// printf("act_group %d num_groups %d\n", pl->act_group, info->num_groups);
	if (info->num_groups > 1 && pl->act_group == 0)	// why gets this one overwritten when going to the next group and why doesn't it understand group 0?
	{
		info->groups[pl->act_group].pipe_in = 0;
		info->groups[pl->act_group].pipe_out = 1;
	}
	else if (pl->act_group > 0 && pl->act_group < info->num_groups - 1)
	{
		info->groups[pl->act_group].pipe_in = 1;
		info->groups[pl->act_group].pipe_out = 1;
	}
	else if (info->num_groups > 1 && pl->act_group == info->num_groups - 1)
	{
		info->groups[pl->act_group].pipe_in = 1;
		info->groups[pl->act_group].pipe_out = 0;
	}
	// printf("act pipe in %d act pipe out %d\n", info->groups[pl->act_group].pipe_in, info->groups[pl->act_group].pipe_out);
	// printf("pipe_in[0] %d pipe_out[0] %d\n", info->groups[0].pipe_in, info->groups[0].pipe_out);
}

int	count_groups(t_info *info)
{
	int num_groups;
	int run;

	num_groups = 1;
	run = -1;
	while (info->input_lexer[++run])
	{
		if (info->input_lexer[1] == NULL) // added by Max 
			return (1);
		if (!strncmp(info->input_lexer[0], "|", 2) || (!strncmp(info->input_lexer[0], " ", 2) && !strncmp(info->input_lexer[1], "|", 2))) // delete second part, if we don't wanna implement that case
			return (1);
		if (!ft_strncmp(info->input_lexer[run], "|", 2))
			num_groups++;
	}
	return (num_groups);
}

void	shift_str_left(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		str[i] = str[i + 1];
}

void	delete_quotationmarks(char	**array)
{
	int	i;
	int	j;
	int	d_quote;
	int	s_quote;

	i = -1;
	d_quote = 0;
	s_quote = 0;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
		{
			if (!d_quote && array[i][j] == '\'')
			{
				shift_str_left(&array[i][j--]);
				s_quote = !s_quote;
			}
			else if (!s_quote && array[i][j] == '\"')
			{
				shift_str_left(&array[i][j--]);
				d_quote = !d_quote;
			}
		}
	}
}

// vor else if()
// if (!d_quote && buf == '\'')
// 	s_quote = !s_quote;
