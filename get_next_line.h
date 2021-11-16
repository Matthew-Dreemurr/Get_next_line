/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:20:56 by mahadad           #+#    #+#             */
/*   Updated: 2021/11/16 13:43:01 by mahadad          ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

/*._-=-_._-=-_. [prototypes] ._-=-_._-=-_._-=-_.*/

typedef struct s_box
{
	char		*tmp;
	t_vector	vec;
	char		*res;
	ssize_t		read_ret;
}				t_box;

char	*get_next_line(int fd);

/*=={ src/vector }==*/

# define VEC_EXIT_FAILURE ((void *)0)
# define VEC_EXIT_SUCCESS ((int)1)
# define VEC_BUFFER_SIZE  ((unsigned long)256)

/**
 * @brief s_vector struc to manage the memory of a char array.
 * 
 * @param len      Actual size use in buff.
 * @param max      Actual max size.
 * @param buff     The buffer is alloc whit (VEC_BUFFER_SIZE + 1).
 */
typedef struct s_vector
{
	size_t	len;
	size_t	max;
	char	*buff;
}				t_vector;

char	*vect_init(t_vector *v, size_t size);
char	*vect_resize(t_vector *v, size_t size);
char	*vect_cat(t_vector *v, char *str);

#endif