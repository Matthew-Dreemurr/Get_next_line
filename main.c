#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
/*
int	main(int ac, char **av)
{
	char	*str = NULL;
	int		fd;
	int		i = 0;

	setbuf(stdout, NULL);
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);

	str = get_next_line(1000);
	printf("[%-5d]:[%p]|", i, &*str); debug_nl(str);
	if (str)
		free(str);
	if (!str)
		printf("NULL\n");
	
	str = get_next_line(-1);
	printf("[%-5d]:[%p]|", i, &*str); debug_nl(str);
	if (str)
		free(str);
	if (!str)
		printf("NULL\n");
	
	str = get_next_line(fd);
	printf("[%-5d]:[%p]|", i, &*str); debug_nl(str);
	if (str)
		free(str);
	if (!str)
		printf("NULL\n");
	
	close(fd);
	return (0);
}

int	main()
{
	t_box data;
	int i = 6;
	vect_init(&data.vec, 128);
	vect_cat(&data.vec, "a\n");
	debug_nl(data.vec.buff);
	debug_nl("=============");
	debug_nl("=============");
	while(data.vec.buff[0])
	{
		debug_nl(ret_next_line(&data));
		debug_nl(data.vec.buff);
		debug_nl("=============");
	}
}
*/