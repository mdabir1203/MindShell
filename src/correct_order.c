#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

# define REDIR_INPUT 4
# define REDIR_INPUT_APPEND 7
# define REDIR_OUTPUT 5
# define REDIR_OUTPUT_APPEND 6
# define PIPE 8
# define WORD 9
# define CMD_FLAGS 11
# define BUILTIN_CMD 10
# define SEPARATOR 12
# define BUILTIN_ECHO 13

//wenn ok dann return 1
int correct_order(int *cat) // this function only makes sence when the argument starts with a >, >>, < or <<
{
    if (*cat != REDIR_INPUT && *cat != REDIR_INPUT_APPEND && *cat != REDIR_OUTPUT && *cat != REDIR_OUTPUT_APPEND) // nur für das erste Argument; danach anders!
		return (-1);
    cat++;
	if (*cat == SEPARATOR)
        cat++;
    if (*cat == WORD)
	    return(1);
	return(-1);
}

int	main(void)
{
    //int array[3] = {4, 12, 9};
    int array[3] = {9, 9, 12};
    //int array[3] = {4, 9, 12};
    //int array[2] = {4, 9};
    int *category;

    category = &array[0];    
    //cathegorizer(order);
    printf("return: %d \n", correct_order(category));
	
	// > testfile.txt -> return 1
	// REDIR_OUTPUT SEPARATOR WORD (input kommt nacheinander rein; return value soll 1 sein)

	// <<hallo.txt
	// REDIR_INPUT_APPEND WORD -> return 1
	return(0);
}
