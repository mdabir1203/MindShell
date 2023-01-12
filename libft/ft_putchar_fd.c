#include "libft.h"

//writes a ascii value to stdout
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
