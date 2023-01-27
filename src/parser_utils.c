#include "../inc/minishell.h"

int	is_redirect(int num)
{
	if (num == REDIR_INPUT_APPEND)
		return (1);
	if (num == REDIR_INPUT)
		return (1);
	if (num == REDIR_OUTPUT_APPEND)
		return (1);
	if (num == REDIR_OUTPUT)
		return (1);
	return (0);
}

/**
 * @brief only call ONCE in the loop? it changes status it is called
 * it returns 1 if it identifies the given str as an redirect i.e. (">", " ", "filename")
 * else returns 0
 * it saves the redirect in the struct groups
 */
int	found_save_redirect(t_parse_lexer *pl, t_info *info, char *act_input_lexer_str) // in init set everything to NULL or 0
{
	int ret;
	static int before_cat = 0;

	ret = 0;
	if (pl->cat == REDIR_INPUT_APPEND || pl->cat == REDIR_INPUT)
	{
		ret = 1;
		before_cat = pl->cat;
		info->groups[pl->act_group].redirect_input = pl->cat;
	}
	if (pl->cat == REDIR_OUTPUT_APPEND || pl->cat == REDIR_OUTPUT)
	{
		ret = 1;
		before_cat = pl->cat;
		info->groups[pl->act_group].redirect_output = pl->cat;
	}
	if (pl->cat == SEPARATOR && is_redirect(before_cat))
		ret = 1;
	if (is_redirect(before_cat))
	{
		if (pl->cat == WORD || pl->cat == FLAG || (pl->cat > BUILTIN_START && pl->cat < BUILTIN_END))
		{
			ret = 1;
			if (before_cat == REDIR_INPUT_APPEND || before_cat == REDIR_INPUT)
				info->groups[pl->act_group].redirect_input_filename = act_input_lexer_str;
			if (before_cat == REDIR_OUTPUT_APPEND || before_cat == REDIR_OUTPUT)
				info->groups[pl->act_group].redirect_output_filename = act_input_lexer_str;
			before_cat = 0;
		}
	}
	return (ret);
}

int	found_save_executable(t_parse_lexer *pl, t_info *info, char *act_input_lexer_str, int i) // malloc so groß wie der lexer string ist
{
	static int already_found_exe = 0;

	if (pl->cat == PIPE || i == 0)
		already_found_exe = 0;
	if (already_found_exe == 0 && !pl->is_red && pl->cat != PIPE && pl->cat != SEPARATOR)// (pl->cat == WORD || pl->cat == FLAG || (pl->cat > BUILTIN_START && pl->cat < BUILTIN_END)))
	{
		info->groups[pl->act_group].cmd = act_input_lexer_str;
		pl->is_exe = 1;
		already_found_exe = 1;
		return (pl->is_exe);
	}
	printf("%p\n", act_input_lexer_str);	// prints out storage adress
	if (act_input_lexer_str == NULL)
		already_found_exe = 0;
	pl->is_exe = 0;
	return (pl->is_exe);
}

char **ft_array_args(char *str)
{
	int	i;
	int	word_count;
	char **array;

	word_count = 0;
	i = -1;
	if(str == NULL || *str == 0)
		return NULL;
	word_count = count_parts(str);
	array = (char **)malloc((sizeof(char *) * (word_count + 1)));
	array[word_count] = 0;
	while (++i < word_count)
	{
		array[i] = (char *) malloc(sizeof(char));
		if (array[i] == NULL)
			error(ERR_MALLOC_SPLIT, NULL); // ATTENTION!!!!!!!!  have to hand over info, or info will be a global
	}
	return (array);
}

int	found_save_arguments(t_parse_lexer *pl, t_group *pt, t_info *info, int i)
{
	//printf("i %d\n", i);
	if (pl->is_exe == 1)
	{
		printf("is_exe %d\n", pl->is_exe);
		while (info->input_lexer[++i])
		{
			pl->cat = categorize(info->input_lexer[i]);
			//printf("cat %d\n", pl->cat);
			pl->is_red = found_save_redirect(pl, info, info->input_lexer[i]);
			if (pl->cat == SEPARATOR)
				continue;							// allowed?
			else if (pl->cat == PIPE || pl->is_red)
				break;								// allowed?
			else
			{
				pt->arg_j++;
				printf("arg_j %d\n", pt->arg_j);
				info->groups[pl->act_group].arguments[pt->arg_j] = info->input_lexer[i];	// creates seg fault for > 1 group
				printf("arg string %s\n", info->groups->arguments[pt->arg_j]);				// creates seg fault for > 1 group
				printf("adress arg %p\n", info->groups[pl->act_group].arguments[pt->arg_j]);	// creates seg fault for > 1 group	
				printf("word\n");
			}	
			printf("i2 %d\n", i);
		}
	}
}

int	count_groups(t_info *info)
{
	int num_groups;
	int run;

	num_groups = 1;
	run = -1;
	while (info->input_lexer[++run])
	{
		if (!ft_strncmp(info->input_lexer[run], "|", 2))
			num_groups++;
	}
	return (num_groups);
}