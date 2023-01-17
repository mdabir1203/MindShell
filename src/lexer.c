#include "../inc/minishell.h"

int	lexer(char *input)
{
	
}

int	sep(char c)
{
	if(c == ' ' || c == '\t' || c == '\n')
		return (1);
