/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:02:38 by mahadad           #+#    #+#             */
/*   Updated: 2021/10/26 14:15:36 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


void	debug_nl(char *str)
{
	while (str && *str)
	{
		if (*str == '\n')
			printf("[\\n]");
		else
			putchar(*str);
		str++;
	}
	puts("\n");
}

/**
 * @brief 
 * 
 * @param buff 
 * @return int 
 */
ssize_t		next_line(char *buff, int fd)
{
	ssize_t	ret;

	ret = read(fd, buff, BUFFER_SIZE);
	if (ret > 0)
		buff[ret] = '\0';
	return (ret);
}

/**
 * @brief Get the next line object
 *
 * @param fd File descriptor to read from.
 * @return char* Read line:  correct behavior NULL: nothing else to read
 *               or anerror occurred.
 */
char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*tmp[OPEN_MAX];
	ssize_t		rret;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	tmp[fd] = NULL;
	while (!len_chrchr(tmp[fd], '\n'))
	{
		rret = next_line(buff, fd);
		if (!rret || rret == -1)
			return (free_return(&tmp[fd]));
		puts("====buff nextline===");
		debug_nl(buff);
		BR;
		if (!len_chrchr(tmp[fd], '\n'))
		{
			tmp[fd] = strjoin_and_free(&(tmp[fd]), buff);
			if (!tmp[fd])
				return (free_return(&tmp[fd]));
			puts("====strjoin===");
			debug_nl(tmp[fd]);
			BR;
		}
	}
	return ("UwU");
}

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	char	*str;
	int		fd;

	setbuf(stdout, NULL);
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		printf("%s\n", str);
		// if (str)
			// free(str);
	}
	close(fd);
	return (0);
}