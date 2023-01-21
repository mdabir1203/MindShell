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

/* defines the data structure. 
In front needs to be typedef to declare the data type */
typedef struct s_node
{
	int				data;
	int				index;
	struct s_node	*link;
}					t_node;

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

int categorizer(struct s_node **a_liste, struct s_node *current, char *str)  // instead of return; write number into an array or a list!!!
{
    if (!ft_strncmp(str, "<<", 3)) // does it really compare with \0 the last sign, please check
	    add_at_end(a_liste, current, REDIR_INPUT_APPEND);
	else if (!ft_strncmp(str, "<", 2))
	    add_at_end(a_liste, current, REDIR_INPUT);
	else if (!ft_strncmp(str, ">", 2))
	    add_at_end(a_liste, current, REDIR_OUTPUT);
	else if (!ft_strncmp(str, ">>", 3))
	    add_at_end(a_liste, current, REDIR_OUTPUT_APPEND);
    else if (!ft_strncmp(str, " ", 1))
	    add_at_end(a_liste, current, SEPARATOR);
	else
        add_at_end(a_liste, current, WORD);
    return (0);
}

/* adds a new node to the list */
int	add_at_end(struct s_node **a_liste, struct s_node *current, int num)
{
	struct s_node	*ptr_a;

	ptr_a = *a_liste;
	current->num = num;
	current->link = NULL;
	if (ptr_a != NULL)
	{
		while (ptr_a->link != NULL)
			ptr_a = ptr_a->link;
		ptr_a->link = current;
	}
	else
		*a_liste = current;
	return (0);
}

//wenn ok dann return 1
int correct_order(struct s_node **a_liste) // this function only makes sence when the argument starts with a >, >>, < or <<
{
    struct s_node *ptr_a;

    ptr_a = *a_liste;
    if (ptr_a->num != REDIR_INPUT && ptr_a->num != REDIR_INPUT_APPEND && ptr_a->num != REDIR_OUTPUT && ptr_a->num != REDIR_OUTPUT_APPEND) // nur für das erste Argument; danach anders!
		return (-1);
    ptr_a = ptr_a->link;
	if (ptr_a->num == SEPARATOR)
        ptr_a = ptr_a->link;
    if (ptr_a->num == WORD)
	    return(1);
	return(-1);
}

/* deletes the whole list from head until NULL */
void	del_list(struct s_node **a_liste)
{
	struct s_node	*ptr_a;
	struct s_node	*temp;

	ptr_a = *a_liste;
	temp = *a_liste;
	while (ptr_a != NULL)
	{
		temp = ptr_a;
		ptr_a = ptr_a->link;
		free(temp);
	}
	free(ptr_a);
}

int	main(void)
{
    char prompt[15] = {"< testfile.txt"};
    char *str;
    struct s_node   *a_liste;
    struct s_node   *current;
    struct s_node   *ptr_a;
    int i;

    a_liste = NULL;
    str = &prompt[0];
    i = -1;
    while (str[++i] != '\0') // loop geht jeden einzelnen char durch; strncmp nimmt aber ganze Teile hervor z.B. für WORD; while return of cat exist?
    {
        current = (struct s_node *)malloc(sizeof(struct s_node));
        if (!current)
            return (0);
        categorizer(&a_liste, current, str);
    }
    ptr_a = *a_liste;
    correct_order(&a_liste, ptr_a);
    free(current);
    del_list(&a_liste);
	// > testfile.txt -> return 1
	// REDIR_OUTPUT SEPARATOR WORD (input kommt nacheinander rein; return value soll 1 sein)

	// <<hallo.txt
	// REDIR_INPUT_APPEND WORD -> return 1
	return(0);
}
