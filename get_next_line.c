/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:02:38 by mahadad           #+#    #+#             */
/*   Updated: 2021/10/20 16:58:17 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

/**
 * @brief 
 * 
 * @param buff 
 * @return int 
 */
ssize_t		next_line(char *buff, int fd)
{
	ssize_t	ret;

	ret = read(fd, &buff, BUFFER_SIZE);
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
	static char	buff[OPEN_MAX][BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		rret;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	buff[fd][0] = '\0';
	while (!len_chrchr(buff[fd], '\0'))
	{
		rret = next_line(buff[fd], fd);
		if (!rret)
			break ;
		else if (rret == -1)
			return (NULL);//TODO
	}
}

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	char	*str;
	int		fd;

	if (ac != 2);
	fd = open(av[1], O_RDONLY);
	while (str = get_next_line(fd))
	{
		printf("%s\n", str);
		free(str);
	}
	return (0);
}