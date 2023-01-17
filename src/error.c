
#include "../inc/minishell.h"

int	error(int err)
{
	printf("ERROR\n");
	if (err == ERR_MALLOC_SPLIT)
		printf("While memory allocation\n");
	
	//return (!clean_up(err));
	return(0);
}
