/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:20:58 by mahadad           #+#    #+#             */
/*   Updated: 2021/11/16 16:03:03 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	if (!dst && !src)
		return (NULL);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned const char *)src;
	while (n > 0)
	{
		n--;
		dst_ptr[n] = src_ptr[n];
	}
	return (dst);
}

char	*vect_init(t_vector *vec, size_t size)
{
	if (!vec || !size)
		return (VEC_EXIT_FAILURE);
	vec->len = 0;
	vec->max = size;
	vec->buff = (char *)malloc(size);
	if (!vec->buff)
		return (VEC_EXIT_FAILURE);
	vec->buff[0] = '\0';
	return (vec->buff);
}

/**
 * @brief Resize the buffer wit `size`.
 * 
 * @param vec 
 * @param size 
 * @return char* 
 */
char	*vect_resize(t_vector *vec, size_t size)
{
	char	*tmp;

	if (!vec || !vec->max)
		return (VEC_EXIT_FAILURE);
	tmp = vec->buff;
	vec->max = size;
	vec->buff = (char *)malloc(vec->max);
	if (!vec->buff)
	{
		vec->buff = tmp;
		return (VEC_EXIT_FAILURE);
	}
	ft_memcpy(vec->buff, tmp, vec->len);
	free(tmp);
	return (vec->buff);
}

/**
 * @brief
 * 
 * @param vec 
 * @param str 
 * @return int 
 */
char	*vect_cat(t_vector *vec, char *str)
{
	size_t	len;

	if (!str && !vec)
		return (VEC_EXIT_FAILURE);
	len = strlen_protect(str);
	while (vec->max < (vec->len + (len + 1)))
		if (!vect_resize(vec, vec->max * 2))
			return (VEC_EXIT_FAILURE);
	while (*str)
		vec->buff[vec->len++] = *str++;
	vec->buff[vec->len] = '\0';
	return (vec->buff);
}

/**
 * @brief Strlen but dont crash with a NULL pointer.
 */
size_t	strlen_protect(const char *s)
{
	char	*start;

	start = (char *)s;
	while (s && *s)
		s++;
	return ((size_t)(s - start));
}