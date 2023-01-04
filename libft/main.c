/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:45:59 by nrenz             #+#    #+#             */
/*   Updated: 2022/01/28 15:09:40 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ft_atoi

// int	main(void)
// {
// 	char	str[] = "12356uio";
// 	int	res;
// 	res = ft_atoi(str);
// 	printf("%d\n", ft_atoi(str));
// 	return (0);
// }

// ft_itoa.c
// int	main(void)
// {
// 	int		n;
// 	char	*p;

// 	n = -2147483647;
// 	p = ft_itoa(n);
// 	printf("%s\n", p);
// 	return (0);
// }

// ft_bzero.c
// int		main(void)
// {
// 	char p[50] = "Hallo ein schönes Wertter!";
// 	int	n;
// 	n = 7;
// 	ft_bzero(p, n);
// 	printf("%s\n", p);
// 	return (0);
// }

// ft_isalnum
// int	main(void)
// {
// 	int	c;
// 	c = 8;
// 	if (ft_isalnum(c) == 0)
// 	{
// 		printf ("This is not alphabet and not digit\n");
// 	}
// 	else
// 	{
// 		printf ("This is alphabet or digit\n");
// 	}
// }

// ft_isalpha
// int	main(void)
// {
// 	int	c;
// 	c = (int) '-';
// 	if (ft_isalpha(c) == 0)
// 	{
// 		printf ("this is not alphabet\n");
// 	}
// 	else
// 	{
// 		printf ("This is alphabet\n");
// 	}
// 	return (0);
// }

// ft_isascii
// int	main(void)
// {
// 	int	c;
// 	c = 'a';
// 	if (ft_isascii(c) == 1)
// 	{
// 		printf ("This is ASCII character\n");
// 	}
// 	else
// 	{
// 		printf ("This is not ASCII character\n");
// 	}
// }

// ft_isdigit
// int	main(void)
// {
// 	int	c;
// 	c = 5;
// 	if (ft_isdigit(c) == 0)
// 	{
// 		printf ("This is not digit\n");
// 	}
// 	else
// 	{
// 		printf ("This is digit\n");
// 	}
// }

// ft_isprint
// int	main(void)
// {
// 	int	c;
// 	c = 122;
// 	if (ft_isprint(c) == 1)
// 	{
// 		printf("This is printable character\n");
// 	}
// 	else
// 	{
// 		printf("This is not printable character");
// 	}
// }

// ft_memchr
// int	main(void)
// {
// 	const char	p[40] = {"Bald sind Weihnachten!"};
// 	char *res;
// 	res = ft_memchr(p, 'b', 25);
// 	printf("%s\n", res);
// 	return (0);
// }

// ft_memcmp
// int	main(void)
// {
// 	char tt1[30] = "Hallo, du schaffst es!";
// 	char tt2[40] = "Hallo, du schaffst es, aber sicher!";
// 	int d;
// 	int result;
// 	d = 10;
// 	result = ft_memcmp(tt1, tt2, d);
// 	printf("%d\n", result);
// 	result = memcmp(tt1, tt2, d);
// 	printf("%d\n", result);
// }

// ft_memcpy
// int	main(void)
// {
// 	char s[30] = {"Neuer Text"};
// 	char d[30] = {"Alter Text"};
// 	int n;
// 	n = 2;
// 	ft_memcpy(d, s, n);
// 	printf("%s\n", d);
// }

// ft_memmove
// int	main(void)
// {
// 	char d[30] = "";
// 	char s[30] = "";
// 	ft_memmove(d, s, ft_strlen(s));
// 	printf("%s\n", d);
// 	return (0);
// }

// ft_memset
// int	 main(void)
// {
// 	char p[50] = "Hallo ein schönes Wertter!";
// 	char s;
// 	s = '$';
// 	int n;
// 	n = 7;
// 	ft_memset(p, s, n);
// 	printf("%s\n", p);
// 	return (0);
// }

// ft_strchr
// int	main(void)
// {
// 	const char	p[40] = "Bald sind Weihnachten!";
// 	char *res;
// 	res = ft_strchr(p, 'd');
// 	printf("%s\n", res);
// }

// ft_strlcat
// int	main(void)
// {
// 	char dest[20] = "Hallo";
// 	char src[20] = "World!";
// 	ft_strlcat(dest, src, 3);
// 	printf("%s\n", dest);
// 	return (0);
// }

// ft_strlcat.c
// int	main(void)
// {
// 	char dest[20] = "Hallo";
// 	char src[20] = "World!";
// 	ft_strlcat(dest, src, ft_strlen(dest));
// 	printf("%s\n", dest);
// 	return (0);
// }

// ft_strlcpy
// int	main(void)
// {
// 	char dest[20] = "Hallo";
// 	char src[20] = "World!";
// 	ft_strlcpy(dest, src, ft_strlen(dest));
// 	printf("%s\n", dest);
// 	return (0);
// }

// ft_strlen
// int	main(void)
// {
// 	char *s = "Hallo Welt!";
// 	int zahl;
// 	zahl = ft_strlen(s);
// 	printf("%d\n", zahl);
// 	//printf("%d", ft_strlen(s));
// }

// ft_strncmp
// int	main(void)
// {
// 	char	s1[20] = {"Hallo"};
// 	char	s2[20] = {"Halla"};
// 	int		res;
// 	res = ft_strncmp(s1, s2, 5);
// 	printf("%d\n", res);
// 	return (0);
// }

// ft_strnstr
// int	main(void)
// {
// 	char	h[20] = "1234567890";
// 	char	n[20] = "89";
// 	char	*res;
// 	res = ft_strnstr(h, n, 10);
// 	// res = ft_strncmp(h, n, 2);
// 	printf("%s\n", res);
// 	return (0);
// }

// ft_strrchr
// int	main(void)
// {
// 	const char	p[40] = {"Bald sind Weihnachten!"};
// 	char *res;
// 	res = ft_strrchr(p, 'z');
// 	printf("%s\n", res);
// 	return (0);
// }

// ft_tolower
// int	main(void)
// {
// 	int c;
// 	c = 'c';
// 	c = ft_toupper(c);
// 	printf("%c\n", c);
// 	return (0);
// }

// ft_toupper
// int	main(void)
// {
// 	int c;
// 	c = 'c';
// 	c = ft_toupper(c);
// 	printf("%c\n", c);
// 	return (0);
// }

// ft_calloc
// int	main(void)
// {
// 	size_t	c;
// 	size_t	s;
// 	char	*memory;
// 	size_t	i;
// 	c = 6;
// 	s = 4;
// 	i = 0;
// 	memory = ft_calloc(c, s);
// 	while (i < c * s)
// 		printf("%c", memory[i++]);
// 	printf("\n");
// 	return (0);
// }

// ft_strdup
// #include <stdio.h>
// #include <string.h>
// int    main()
// {
//char	*str = "123456";

//printf("%s\n", ft_strdup(str));
//printf("%s\n", strdup(str));
// }

// ft_substr.c
// int	main(void)
// {
// 	char			*s;
// 	char			*res;
// 	unsigned int	start;
// 	size_t			l;
// 	s = "Das ist der Hauptstring";
// 	start = 5;
// 	l = 3;
// 	res = ft_substr(s, start, l);
// 	printf("%s\n", res);
// 	return (0);
// }

// int main(void)
// {
// 	char	**res;
// 	char		c;
// 	unsigned int i;
// 	i = 0;
// 	c = '_';
// 	char *str = "_UNDEUXTROIS";
// 	res = ft_split(str, c);
// 	while (i < ft_wordcount(str, c) + 1)
// 		printf("%s\n", res[i++]);
// 	return (0);
// }

// ft_striteri.c
// int	main(void)
// {
// 	char	*p = "Halli Gallo Welt!";
// 	printf("\nBefore iteri: %s", p);
// 	ft_striteri(p, testfunction);
// 	printf("\nAfter iteri:  %s", p);
// 	return (0);
// }

// ft_strjoin.c
// int	main(void)
// {
// 	char			*s1;
// 	char			*s2;
// 	char			*res;
// 	s1 = "erstellen";
// 	s2 = "zusammenfügen";
// 	res = ft_strjoin(s1, s2);
// 	printf("%s\n", res);
// 	return (0);
// }

// ft_strmapi.c
// int	main(void)
// {
// 	char	*teststring1 = "Hallo wie geht es dir?";
// 	char	*test_result = ft_strmapi(teststring1, ft_testfunction);
// 	printf("\nTest 1: %s - wird zu\n %s",teststring1, test_result);	
// }

// ft_strtrim.c
// int	main(void)
// {
// 	char	*s1;
// 	char	*set;
// 	char	*res;
// 	s1 = "abcHundMausKatzedef";
// 	set = "abcdef";
// 	res = ft_strtrim(s1, set);
// 	printf("%s", res);
// 	return (0);
// }

// ft_putchar_fd
// int	main(void)
// {
// 	ft_putchar_fd('z', 1);
// 	ft_putchar_fd('\n', 1);
// }

// ft_puendl_fd.c
// int	main(void)
// {
// 	ft_putendl_fd("Heir ist ein String", 1);
// }

// ft_putnbr_fd.c
// int	main(void)
// {
// 	ft_putnbr_fd(34568, 1);
// }

// ft_putstr_fd.c
// int	main(void)
// {
// 	ft_putstr_fd("Hier ist ein String", 1);
// }

// Bonus
// ft_lstnew
// int	main(void)
// {
// 	char	*content = "Hier ist meine neue linked List";
// 	t_list	*newlist;
// 	newlist = ft_lstnew(content);
// 	printf("%s", newlist->content);
// 	return (0);	
// }
