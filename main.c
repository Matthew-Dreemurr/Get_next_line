#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	char	*str;
	int		fd;
	int		i = 0;

	setbuf(stdout, NULL);
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		// printf("[%-5d]:|%s|", i, str);
		if (str)
			free(str);
		i++;
	}
	close(fd);
	return (0);
}