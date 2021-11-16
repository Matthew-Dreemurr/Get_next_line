#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void	debug_nl(const char *str)
{
	printf("\033[0;33m");
	while (str && *str)
	{
		if (*str == '\n')
			printf("[\\n]");
		else
			putchar(*str);
		str++;
	}
	printf("\n");
	printf("\033[0m");
}


int	main(int ac, char **av)
{
	char	*str = NULL;
	int		fd;
	int		i = 0;

	setbuf(stdout, NULL);
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		printf("[%-5d]:[%p]|", i, &*str); debug_nl(str);
		if (str)
			free(str);
		i++;
	}
	if (!str)
		printf("NULL\n");
	close(fd);
	return (0);
}
/**
size_t	strlen_protect(const char *s)
{
	char	*start;

	start = (char *)s;
	while (s && *s)
		s++;
	return ((size_t)(s - start));
}
static size_t	fk_strlen(const char *str)
{
	const char	*start;

	start = str;
	while (str && *str)
		str++;
	return ((size_t)(str - start));
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	char	*start;

	ret = (char *)malloc((fk_strlen(s1) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	start = ret;
	while (*s1)
	{
		*ret = *s1;
		ret++;
		s1++;
	}
	*ret = '\0';
	return (start);
}
char	*ret_next_line(char **str)
{
	char	*ret;
	char	*str_ptr;
	char	*ptr;
	size_t	len;

	len = len_chrchr(*str, '\n');
	if (!len)
		len = strlen_protect(*str);
	ret = (char *)malloc((1 + len) * sizeof(char));
	if (!ret)
		return (NULL);
	str_ptr = *str;
	ptr = ret;
	while (*str_ptr)
	{
		*ptr++ = *str_ptr;
		if (*str_ptr++ == '\n')
			break ;
	}
	*ptr = '\0';
	ptr = *str;
	while (*str_ptr)
		*ptr++ = *str_ptr++;
	*ptr = '\0';
	return (ret);
}
size_t	len_chrchr(char *str, char c)
{
	char	*start;

	start = str;
	while (str && *str && *str != c)
		str++;
	if (str && *str == c)
		str++;
	else
		return (0);
	return ((size_t)(str - start));
}
int main()
{
	char	*str = ft_strdup("12345\nabcdef\nxyz");
	int i = 4;

	while (i--)
	{
		printf("|%s|\n", ret_next_line(&str));
	}
	return (0);
}
**/