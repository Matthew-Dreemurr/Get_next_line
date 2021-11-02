/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:02:38 by mahadad           #+#    #+#             */
/*   Updated: 2021/11/02 15:26:57 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	manage_next_line(t_box *b)
{
	b->fill += b->r_ret;
	b->index = len_chrchr(b->buff, '\n', b->fill);
	b->tmp = ft_substr(b->buff, 0, b->index + (b->index != b->fill));
	b->r = strjoin_and_free(&b->r, b->tmp);
	free(b->tmp);
	ft_memcpy(b->buff, b->buff + b->index + (b->index != b->fill),
		b->fill - b->index - (b->index != b->fill));
	b->fill = b->fill - b->index - (b->index != b->fill);
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
	b[fd].r = NULL;
	while (1)
	{
		b[fd].r_ret = read(fd, (b[fd].buff + (b[fd].fill)),
				BUFFER_SIZE - b[fd].fill);
		if (!b[fd].r_ret && !b[fd].fill)
		{
			b[fd].fill = 0;
			return (b[fd].r);
		}
		if (b[fd].r_ret == -1)
		{
			b[fd].fill = 0;
			return (NULL);
		}
		manage_next_line(&b[fd]);
		if (b[fd].r && b[fd].r[0]
			&& b[fd].r[strlen_protect(b[fd].r) - 1] == '\n')
			break ;
	}
	return (b[fd].r);
}
