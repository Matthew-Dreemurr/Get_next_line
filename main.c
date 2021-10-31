#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void	debug_nl(char *str)
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
	puts("\n");
	printf("\033[0m");
}

int	main(int ac, char **av)
{
	char	*str;
	int		fd;
	int		i = 0;

	setbuf(stdout, NULL);
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	/*while ((*/str = get_next_line(fd);/*))*/
	// {
		printf("[%-5d]: |", i); debug_nl(str);
		if (str)
			free(str);
		// i++;
	// }
	// if (!str)
		// printf("NULL\n");
	close(fd);
	return (0);
}