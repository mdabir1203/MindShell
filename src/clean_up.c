
#include "../inc/minishell.h"

void	clean_up(int clean_up_code)
{
	if (clean_up_code == CTRL_D_PRESSED)
		exit(0);
}
