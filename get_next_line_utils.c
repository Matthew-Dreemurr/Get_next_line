/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:20:58 by mahadad           #+#    #+#             */
/*   Updated: 2021/10/26 14:11:45 by mahadad          ###   ########.fr       */
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

/**
 * @brief malloc size of (`s1` + `s2` + 1).
 *        `s1` and `s2` can be NULL.
 * 
 * @param s1 The prefix string can be NULL.
 * @param s2 The suffix string can be NULL.
 * @return char* Pointer to the allocate memory.
 */
static char	*alloc_init(const char *s1, const char *s2)
{
	const char	*s1_p;
	const char	*s2_p;

	s1_p = s1;
	s2_p = s2;
	while (s1_p && *s1_p)
		s1_p++;
	while (s2_p && *s2_p)
		s2_p++;
	// printf("malloc size:%lu\n",(1 + (s1_p - s1) + (s2_p - s2)));
	return ((char *)malloc(sizeof(char) * (1 + (s1_p - s1) + (s2_p - s2))));
}

/**
 * @brief Allocates (with malloc(3)) and returns a new
 *        string, which is the result of the concatenation
 *        of ’s1’ and ’s2’ and free the `s1`.
 *        `s1` and `s2` can be NULL.
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
		return (NULL);
	s1_ptr = *s1;
	ret_ptr = ret;
	while (s1_ptr && *s1_ptr)
		*ret++ = *s1_ptr++;
	while (s2 && *s2)
		*ret++ = *s2++;
	*ret = '\0';
	// printf("ret:|%s|\n", ret_ptr);
	if (s1 && *s1)
		free (*s1);
	return (ret_ptr);
}

char	*free_return(char **ptr)
{
	if (*ptr)
		free(*ptr);
	return (NULL);
}