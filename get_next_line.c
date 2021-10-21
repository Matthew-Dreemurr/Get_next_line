/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:02:38 by mahadad           #+#    #+#             */
/*   Updated: 2021/10/21 15:40:08 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	buff_manager(char *buffer, char *tmp)
{
	size_t	len;
	char	*start_tmp;

	start_tmp = tmp;
	tmp = (char *)malloc(sizeof(char) * (len_chrchr(buffer, '\n') + 1));
	while (*buffer)
	{
		*tmp = *buffer++;
		if (*tmp++ == '\n')
			break ;
	}
	while (*buffer)
		*buffer++ = *buffer++;//TODO erase buffer and dont call next_line if '\n' inside
	
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
	static char	buff[OPEN_MAX][BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		rret;

	(void)tmp;
	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	buff[fd][0] = '\0';
	size_t debug;
	while (!(debug = len_chrchr(buff[fd], '\n')))
	{
		rret = next_line(buff[fd], fd);
		printf(
		"buff|\n"
		"%s\n"
		"rret :[%lu]\n"
		"debug:[%lu]\n",
		buff[fd], rret, debug);
		BR;
		if (!rret)
			break ;
		else if (rret == -1)
			return (NULL);
		else if (len_chrchr(buff[fd], '\n'))
			buff_manager(buff[fd], tmp);//WIP
	}
	return (NULL);
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
		free(str);
	}
	close(fd);
	return (0);
}