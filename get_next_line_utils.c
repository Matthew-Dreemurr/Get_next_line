/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:20:58 by mahadad           #+#    #+#             */
/*   Updated: 2021/10/26 12:10:51 by mahadad          ###   ########.fr       */
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
	while (*str && *str != c)
		str++;
	if (*str == c)
		str++;
	else
		return (0);
	return ((size_t)(str - start));
}
