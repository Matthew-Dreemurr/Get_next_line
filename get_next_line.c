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
 * @brief If malloc fail free `*str`
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
		return (free_return(str));
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
ssize_t	read_next_line(char *buff, int fd)
{
	ssize_t	ret;

	ret = read(fd, buff, BUFFER_SIZE);
	if (ret > 0)
		buff[ret] = '\0';
	return (ret);
}

/**
 * @brief The only way i find to check if we have enough space for the buff
 * 
 * @param ptr 
 * @return char* 
 */
char	*alloc_buffer(char **ptr)
{
	*ptr = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
	return (*ptr);
}

char	*return_manager(char *tmp)
{
	if (len_chrchr(tmp, '\n'))
		return (ret_next_line(&tmp));
	else if (!strlen_protect(tmp))
		return (free_return(&tmp));
	else
		return (strjoin_and_free(&tmp, NULL));
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
	static t_box	b[FOPEN_MAX];

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	if (!alloc_buffer(&b[fd].buff))
		return (NULL);
	b[fd].r_ret = 1;
	b[fd].buff[0] = '\0';
	b[fd].tmp = NULL;
	while (b[fd].r_ret && !len_chrchr(b[fd].buff, '\n'))
	{
		b[fd].r_ret = read_next_line(b[fd].buff, fd);
		if (b[fd].r_ret < 0)
		{
			if (b[fd].tmp)
				free(b[fd].tmp);
			return (free_return(&b[fd].buff));
		}
		if (b[fd].r_ret)
			b[fd].tmp = strjoin_and_free(&(b[fd].tmp), b[fd].buff);
		if (!b[fd].tmp)
			return (free_return(&(b[fd].buff)));
	}
	free(b[fd].buff);
	return (return_manager(b[fd].tmp));
}
