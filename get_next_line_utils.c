/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:20:58 by mahadad           #+#    #+#             */
/*   Updated: 2021/11/02 15:31:50 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief malloc size of (`s1` + `s2` + 1).
 *        `s1` and `s2` can be NULL.
 * 
 * @param s1 The prefix string can be NULL.
 * @param s2 The suffix string can be NULL.
 * @return char* Pointer to the allocate memory.
 */
char	*alloc_init(const char *s1, const char *s2)
{
	const char	*s1_p;
	const char	*s2_p;

	s1_p = s1;
	s2_p = s2;
	while (s1_p && *s1_p)
		s1_p++;
	while (s2_p && *s2_p)
		s2_p++;
	return ((char *)malloc(sizeof(char) * (1 + (s1_p - s1) + (s2_p - s2))));
}

/**
 * @brief Allocates (with malloc(3)) and returns a new
 *        string, which is the result of the concatenation
 *        of ’s1’ and ’s2’ and free the `s1`.
 *        `s1` and `s2` can be NULL.
 *        In case dat alloc fail, `*s1` will be free.
 *
 * @param s1 The prefix string can be NULL.
 * @param s2 The suffix string can be NULL.
 * @return char* The new string. NULL if the allocation fails.
 */
char	*strjoin_and_free(char **s1, char const *s2)
{
	char	*ret;
	char	*ret_ptr;
	char	*s1_ptr;

	ret = alloc_init(*s1, s2);
	if (!ret)
		return (free_return(s1));
	s1_ptr = *s1;
	ret_ptr = ret;
	while (s1_ptr && *s1_ptr)
		*ret++ = *s1_ptr++;
	while (s2 && *s2)
		*ret++ = *s2++;
	*ret = '\0';
	if (s1 && *s1)
	{
		free (*s1);
		*s1 = NULL;
	}
	return (ret_ptr);
}

char	*free_return(char **ptr)
{
	if (*ptr)
		free(*ptr);
	return (NULL);
}

/**
 * @brief Allocates (with malloc(3)) and returns a substring
 *        from the string ’s’.
 *        The substring begins at index ’start’ and is of maximum size ’len’.
 * 
 * @param s      The string from which to create the substring.
 * @param start  The start index of the substring in the string ’s’.
 * @param len    The maximum length of the substring.
 * @return char* The substring. NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*str_ptr;

	if (!s)
		return (NULL);
	s += start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str_ptr = str;
	while (len-- > 0)
		*str_ptr++ = *s++;
	*str_ptr = '\0';
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned const char *)src;
	while (i < n)
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
	return (dst);
}
