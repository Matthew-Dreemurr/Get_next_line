/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:20:56 by mahadad           #+#    #+#             */
/*   Updated: 2021/10/26 14:26:12 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*._-=-_._-=-_. [//TODO REMOVE] ._-=-_._-=-_.*/
#define BR getchar();
#define BRP(x) printf(x);
#include <stdio.h>
/*._-=-_._-=-_. [//TODO REMOVE] ._-=-_._-=-_.*/

/*._-=-_._-=-_. [includes] ._-=-_._-=-_.*/
# include <limits.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

/*._-=-_._-=-_. [define] ._-=-_._-=-_._-=-_.*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

/*._-=-_._-=-_. [prototypes] ._-=-_._-=-_._-=-_.*/
/*.-| get_next_line.c |-.*/

char	*get_next_line(int fd);
ssize_t	read_next_line(char *buff, int fd);
char	*ret_next_line(char **str);

/*.-| get_next_line_utils.c |-.*/

size_t	len_chrchr(char *str, char c);
char	*alloc_init(const char *s1, const char *s2);
char	*strjoin_and_free(char **s1, char const *s2);
char	*free_return(char **ptr);
# endif