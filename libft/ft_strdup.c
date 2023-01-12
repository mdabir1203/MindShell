#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		length;
	char	*target1;

	length = 0;
	while (s1[length])
		length++;
	target1 = malloc(sizeof(char) * length + 1);
	if (!target1)
		return (NULL);
	i = 0;
	while (s1[i])
	{
			target1[i] = s1[i];
		i++;
	}
	target1[i] = '\0';
	return (target1);
}
