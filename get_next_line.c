/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:02:38 by mahadad           #+#    #+#             */
/*   Updated: 2021/10/28 17:46:43 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief 
 * 
 * @param str 
 * @return char* 
 */
char	*ret_next_line(char **str)
{
	char	*ret;
	char	*str_ptr;
	char	*ptr;
	ret = (char *)malloc((1 + len_chrchr(*str, '\n')) * sizeof(char));
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

/**
 * @brief Read in the `fd`, write in `buff` and terminate the string /w a '\0'.
 * 
 * @param buff
 * @return int
 */
char	*read_next_line(int fd)
{
	ssize_t	read_ret;
	char	*ret;
	char	buff[BUFFER_SIZE + 1];

	ret = NULL;
	read_ret = read(fd, buff, BUFFER_SIZE);
	if (read_ret < 1)
		return (NULL);
	buff[read_ret] = '\0';
	printf("READ |");debug_nl(buff);
	ret = strjoin_and_free(&ret, buff);
	if (!len_chrchr(ret, '\n') && read_ret)
		return (strjoin_and_free(&ret, read_next_line(fd)));
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
	static char		*tmp[OPEN_MAX];
	const char		*debug;

	if (fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	tmp[fd] = read_next_line(fd);
	if (!tmp[fd])
		return (NULL);
	//On met ce qui a ete lu dans tmp

	//Si le buffer n'as pas pas de '\n' on relis jusqu'a en trouver un en recursif
	//On renvois la concatneation du nouveau read avec les reste dans tmp
	// if (!len_chrchr(tmp[fd], '\n') && rret)
		// return (tmp[fd] = strjoin_and_free(&tmp[fd], get_next_line(fd)));
	printf("leftover |"); debug_nl(tmp[fd]);
	debug = ret_next_line(&tmp[fd]);
	printf("leftover clean |"); debug_nl(tmp[fd]);
	printf("return |"); debug_nl(debug); return ((char *)debug);
}