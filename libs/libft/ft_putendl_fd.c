#include "libft.h"

//writes a string to a filedescriptor
void	ft_putendl_fd(char *s, int fd)
{
	size_t	length;

	if (s)
	{
		length = ft_strlen(s);
		write(fd, s, length);
		write(fd, "\n", 1);
	}
}
