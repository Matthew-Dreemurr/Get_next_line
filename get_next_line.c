/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:02:38 by mahadad           #+#    #+#             */
/*   Updated: 2021/11/15 16:38:21 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief `strlen` but whiout crash when `NULL` and stop count when find
 *         the first occurence of char `c`
 * 
 * @param str      the tring to pars
 * @param c        the caracter to find
 * @return size_t  the number of character befor `c` (`c` include)
 */
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

size_t	strlen_protect(const char *s)
{
	char	*start;

	start = (char *)s;
	while (s && *s)
		s++;
	return ((size_t)(s - start));
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
	while (1)
	{
		b[fd].r_ret = read(fd, b[fd].buff, BUFFER_SIZE);
		if (b[fd].r_ret == -1)
			return (NULL);
		if (!b[fd].r_ret && !strlen_protect(b[fd].tmp))
			return (NULL);
		if (!b[fd].r_ret)
			break ;
		b[fd].tmp = strjoin_and_free(&b[fd].tmp, b[fd].buff);
		if (!b[fd].tmp)
			return (free_return(&b[fd].tmp));
		if (b[fd].r_ret && len_chrchr(b[fd].tmp, '\n'))
			break ;
	}
	b[fd].r = ret_next_line(&b[fd].tmp);
	if (!b[fd].r)
		return (free_return(&b[fd].tmp));
	return (b[fd].r);
}
