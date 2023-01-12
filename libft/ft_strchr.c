#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	length;

	length = 0;
	while (s[length])
	{
		if (s[length] == (char)c)
			return ((char *)s + length);
		length++;
	}
	if (s[length] == (char)c)
		return ((char *)s + length);
	return (NULL);
}
