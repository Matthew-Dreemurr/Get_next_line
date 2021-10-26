/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:02:38 by mahadad           #+#    #+#             */
/*   Updated: 2021/10/26 12:17:09 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	buff_manager(char *buffer, char **tmp)
{
	char *ptr;
	char *ptrb;

	ptrb = buffer;
	*tmp = (char *)malloc(sizeof(char) * (len_chrchr(buffer, '\n') + 1));
	ptr = *tmp;
	if (!*tmp)
		return (0);
	while (*buffer && !(*buffer == '\n'))
	{
		*ptr++ = *buffer++;
	}
	*ptr = '\0';
	while (*buffer)
	{
		*ptrb++ = *buffer++;
	}
	*ptrb = '\0';
	return (1);
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
	while (!len_chrchr(buff[fd], '\n'))
	{
		rret = next_line(buff[fd], fd);
		if (!rret)
			break ;
		else if (rret == -1)
			return (NULL);
	}
	debug_nl(buff[fd]);
	BR;
	if(!buff_manager(buff[fd], &tmp))//WIP
		return (NULL);
	return (tmp);
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
		// printf("%s\n", str);
		// if (str)
			// free(str);
	}
	close(fd);
	return (0);
}