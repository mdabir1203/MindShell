#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*target;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if ((size_t)start > ft_strlen(s))
		len = 0;
	else if (len + (size_t)start > ft_strlen(s))
		len = ft_strlen(s) - (size_t)start;
	target = malloc(sizeof(*s) * (len + 1));
	if (!target)
		return (NULL);
	while (i < len)
	{
		target[i] = s[start + i];
		i++;
	}
	target[i] = '\0';
	return (target);
}
