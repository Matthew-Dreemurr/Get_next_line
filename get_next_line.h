/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:20:56 by mahadad           #+#    #+#             */
/*   Updated: 2021/11/15 16:23:18 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*._-=-_._-=-_. [includes] ._-=-_._-=-_.*/

# include <limits.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define BUFFER_SIZE 128

// #include "wraloc.h"
/*._-=-_._-=-_. [prototypes] ._-=-_._-=-_._-=-_.*/

typedef struct s_box
{
	char		*tmp;
	char		buff[BUFFER_SIZE];
	char		*r;
	ssize_t		r_ret;
	size_t		fill;
	size_t		index;
}				t_box;

char	*get_next_line(int fd);
void	manage_next_line(t_box *b);
size_t	strlen_protect(const char *s);
char	*alloc_init(const char *s1, const char *s2);
char	*strjoin_and_free(char **s1, char const *s2);
char	*free_return(char **ptr);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	len_chrchr(char *str, char c);

#endif