#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		while (haystack[i + count] == needle[count] \
		&& needle[count] && (i + count) < len)
		{
			if (needle[count + 1] == '\0')
				return ((char *)haystack + i);
			count++;
		}
		i++;
		count = 0;
	}
	return (0);
}
