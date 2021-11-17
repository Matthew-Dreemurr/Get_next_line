/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:02:38 by mahadad           #+#    #+#             */
/*   Updated: 2021/11/17 12:28:02 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief 
 * 
 * @param ptr 
 * @param ret 
 * @return int 
 */
char	*free_return(char **ptr1, char **ptr2, char *ret, size)//TODO init vec.max 0
{
	if (*ptr1)
	{
		free (*ptr1);
		*ptr1 = NULL;
	}
	if (*ptr2)
	{
		free (*ptr2);
		*ptr2 = NULL;
	}
	return (ret);
}

size_t	is_end_of_line(char *str, size_t max)
{
	size_t	len;

	len = 0;
	if (!str || !max)
		return (0);
	while (len < max)
	{
		if (str[len] == '\n' || str[len] == '\0')
			return (1);
		len++;
	}
	return (0);
}

void	clear_vect_next_line(char *src, char *dst, size_t *vec_len)
{
	char	*ptr;

	ptr = dst;
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	*vec_len = strlen_protect(dst);
}

char	*ret_next_line(t_box *data)
{
	char	*ptr1;
	char	*ptr2;

	ptr1 = data->vec.buff;
	while (*ptr1)
		if (*ptr1++ == '\n')
			break ;
	data->res = (char *)malloc((size_t)((ptr1 - data->vec.buff) + 1));
	if (!data->res)
		return (NULL);
	ptr1 = data->vec.buff;
	ptr2 = data->res;
	while (*ptr1)
	{
		*ptr2++ = *ptr1;
		if (*ptr1++ == '\n')
			break ;
	}
	*ptr2 = '\0';
	clear_vect_next_line(ptr1, data->vec.buff, &data->vec.len);
	return (data->res);
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
	static t_box	data[FOPEN_MAX];

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	if (!data[fd].vec.max && !vect_init(&data[fd].vec, BUFFER_SIZE))
		return (NULL);
	while (1)
	{
		data[fd].read_ret = read(fd, data[fd].buffer, BUFFER_SIZE);
		if (data[fd].read_ret == -1)
			return (free_return(&data[fd].vec.buff, NULL, NULL));
		data[fd].buffer[data[fd].read_ret] = '\0';
		if (!vect_cat(&data[fd].vec, data[fd].buffer))
			return (free_return(&data[fd].vec.buff, NULL, NULL));
		if (is_end_of_line(data[fd].buffer, data[fd].read_ret))
			break ;
		if (!data[fd].read_ret)
			break ;
	}
	if (!ret_next_line(&data[fd]))
		return (free_return(&data[fd].vec.buff, NULL, NULL));
	if ((!data[fd].res[0] && !data[fd].read_ret))
		return (free_return(&data[fd].vec.buff, &data[fd].res, NULL));
	return (data[fd].res);
}
