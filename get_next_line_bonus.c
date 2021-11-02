/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:02:38 by mahadad           #+#    #+#             */
/*   Updated: 2021/11/02 15:14:38 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		b[fd].r_ret = read(fd, (b[fd].buff + (b[fd].fill)), BUFFER_SIZE - b[fd].fill);
		if (!b[fd].r_ret && !b[fd].fill)
		{
			b[fd].fill = 0;
			return (b[fd].r);//free buff
		}
		if (b[fd].r_ret == -1)
		{
			b[fd].fill = 0;
			return (NULL);//free
		}
		b[fd].fill += b[fd].r_ret;
		b[fd].index = len_chrchr(b[fd].buff, '\n', b[fd].fill);
		b[fd].tmp = ft_substr(b[fd].buff, 0, b[fd].index + (b[fd].index != b[fd].fill));
		b[fd].r = strjoin_and_free(&b[fd].r, b[fd].tmp);
		free(b[fd].tmp);
		ft_memcpy(b[fd].buff, b[fd].buff + b[fd].index + (b[fd].index != b[fd].fill), b[fd].fill - b[fd].index - (b[fd].index != b[fd].fill));
		b[fd].fill = b[fd].fill - b[fd].index - (b[fd].index != b[fd].fill);
		if (b[fd].r && b[fd].r[0] && b[fd].r[strlen_protect(b[fd].r) - 1] == '\n')
			break ;
	}
	return (b[fd].r);
}
